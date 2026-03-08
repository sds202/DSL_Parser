# tests/test_chat_func.py
import pytest


@pytest.fixture(scope="module", autouse=True)
def init_dsl(client):
    """所有功能测试前加载 DSL"""
    resp = client.post_admin("./DSL_script/test1.dsl")
    assert resp.status_code == 200, "DSL 初始化失败"


def test_01_easy_reply(client):
    """验证简单回复"""
    resp = client.post_msg("auto_01", "你好。")
    assert resp.status_code == 200
    assert "您好" in resp.text


def test_03_long_intent_flow(client):
    """简单长意图"""
    uid = "auto_03"

    r1 = client.post_msg(uid, "我想查一下订单状态")
    assert "订单号" in r1.text

    r2 = client.post_msg(uid, "订单号是3330")
    assert "已发货" in r2.text


def test_04_auto_slot(client):
    """自动填槽"""
    uid = "auto_04"

    r1 = client.post_msg(uid, "我想查一下订单状态，订单号是3331")
    assert "订单号" not in r1.text
    assert "已签收" in r1.text


def test_05_long_intent_2(client):
    """两个槽位"""
    uid = "auto_05"

    r1 = client.post_msg(uid, "我想要退款订单")
    assert "哪个订单" in r1.text

    r2 = client.post_msg(uid, "订单号是3330")
    assert "退款原因" in r2.text

    r3 = client.post_msg(uid, "商品有问题")
    assert "已提交" in r3.text


def test_06_auto_slot_2(client):
    uid = "auto_06"

    r1 = client.post_msg(uid, "我想要退款订单，订单号是3331，退款原因是商品降价了")
    assert "哪个订单" not in r1.text
    assert "退款原因" not in r1.text
    assert "失败" in r1.text


def test_07_logic_interrupt(client):
    uid = "auto_07"

    r1 = client.post_msg(uid, "查订单")
    assert "订单号" in r1.text

    r2 = client.post_msg(uid, "你好")
    assert "您好" in r2.text


def test_08_ask_out_of_order(client):
    uid = "auto_08"

    r1 = client.post_msg(uid, "我要退款")
    assert "订单" in r1.text

    r2 = client.post_msg(uid, "因为我不喜欢这个商品")
    assert "订单号" in r2.text

    r3 = client.post_msg(uid, "订单号是3331")
    assert "退款原因" not in r3.text
    assert "申请" in r3.text


def test_09_partial_slot(client):
    uid = "auto_09"

    r1 = client.post_msg(uid, "我要退款，因为商品坏了")
    assert "哪个订单" in r1.text
    assert "原因" not in r1.text

    r2 = client.post_msg(uid, "要退款的订单号是10086")
    assert "申请" in r2.text
