# tests/test_chat_exception.py
import pytest


@pytest.fixture(scope="module", autouse=True)
def init_dsl(client):
    resp = client.post_admin("./DSL_script/test1.dsl")
    assert resp.status_code == 200


def test_01_unknown_intent(client):
    resp = client.post_msg("auto_01", "今天天气怎么样？")
    assert resp.status_code == 200
    assert ("您好" in resp.text) or ("不知道" in resp.text)


def test_02_empty_input(client):
    resp = client.post_msg("auto_02", "")
    assert resp.status_code == 200
    assert "您好" in resp.text or "大模型异常" in resp.text


def test_03_missing_header(client):
    import requests

    resp = requests.post(
        "http://localhost:8080/",
        data="你好".encode("utf-8"),
        headers={"Content-Type": "text/plain; charset=utf-8"},
        timeout=5
    )

    if resp.status_code == 200:
        assert "visitor" in resp.text
    else:
        assert resp.status_code >= 400


def test_04_huge_payload(client):
    huge_text = "测试" * 5000
    resp = client.post_msg("auto_04", huge_text)
    assert resp.status_code != 500
    assert resp.status_code != 200


def test_05_truncated_payload(client):
    huge_text = "1234567890" * 100
    resp = client.post_msg("auto_05", huge_text)
    assert "截断" in resp.text or "稍后重试" in resp.text

def test_06_database_exception(client):
    uid = "auto_06"

    r1 = client.post_msg(uid, "我想查一下订单状态")
    assert "订单号" in r1.text

    r2 = client.post_msg(uid, "订单号是666")
    assert "稍后重试" in r2.text
