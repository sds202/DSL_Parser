# tests/test_switch_dsl_exception.py
import pytest


@pytest.fixture(scope="module", autouse=True)
def init_dsl_v1(client):
    """保证测试开始时 DSL 是正常的"""
    resp = client.post_admin("./DSL_script/test1.dsl")
    assert resp.status_code == 200


def test_01_invalid_path(client):
    """错误的 DSL 路径"""
    uid = "auto_01"

    r1 = client.post_msg(uid, "你好。")
    assert "欢迎来到我们的商城" in r1.text

    r2 = client.post_admin("./DSL_script/not_exist.dsl")
    assert r2.status_code != 200

    r3 = client.post_msg(uid, "你好。")
    assert "欢迎来到我们的商城" in r3.text


def test_02_missing_path(client):
    """缺少 DSL 路径"""
    uid = "auto_02"

    r1 = client.post_msg(uid, "你好。")
    assert "欢迎来到我们的商城" in r1.text

    r2 = client.post_admin("")
    assert r2.status_code != 200

    r3 = client.post_msg(uid, "你好。")
    assert "欢迎来到我们的商城" in r3.text


def test_03_less_valid_dsl_file(client):
    """轻微错误的 DSL 文件"""
    uid = "auto_03"

    r1 = client.post_msg(uid, "你好。")
    assert "欢迎来到我们的商城" in r1.text

    r2 = client.post_admin("./DSL_script/less_valid.dsl")
    assert r2.status_code == 500


def test_04_invalid_dsl_file_unknown_call(client):
    """错误 DSL：未知类或方法"""
    uid = "auto_04"

    r1 = client.post_msg(uid, "你好。")
    assert "欢迎来到我们的商城" in r1.text

    r2 = client.post_admin("./DSL_script/invalid1.dsl")
    assert r2.status_code == 500


def test_05_invalid_dsl_file_keyword_error(client):
    """错误 DSL：关键字错误"""
    uid = "auto_05"

    r1 = client.post_msg(uid, "你好。")
    assert "欢迎来到我们的商城" in r1.text

    r2 = client.post_admin("./DSL_script/invalid2.dsl")
    assert r2.status_code == 500


def test_06_invalid_dsl_file_param_count(client):
    """错误 DSL：参数数量不正确"""
    uid = "auto_06"

    r1 = client.post_msg(uid, "你好。")
    assert "欢迎来到我们的商城" in r1.text

    r2 = client.post_admin("./DSL_script/invalid3.dsl")
    assert r2.status_code == 500
