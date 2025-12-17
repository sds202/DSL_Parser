# tests/test_switch_dsl.py
import pytest
import time


@pytest.fixture(scope="module", autouse=True)
def init_dsl_v1(client):
    """默认加载 DSL V1"""
    resp = client.post_admin("./DSL_script/test1.dsl")
    assert resp.status_code == 200, "DSL V1 初始化失败"


def test_01_dsl_switch_basic(client):
    """DSL 热更新基本功能验证"""
    uid = "auto_01"

    # 1️⃣ 验证 DSL V1 正常
    r1 = client.post_msg(uid, "我想查一下订单状态，订单号是3331")
    assert "订单号" not in r1.text
    assert "已签收" in r1.text

    # 2️⃣ 切换到 DSL V2
    r2 = client.post_admin("./DSL_script/test2.dsl")
    assert r2.status_code == 200, "DSL V2 热更新失败"

    # 3️⃣ 验证 DSL V2 生效
    r3 = client.post_msg(uid, "我要使用优惠券，优惠券代码是6660")
    assert "成功使用" in r3.text


def test_02_switch_during_chat(client):
    """聊天中途切换 DSL"""
    uid = "auto_02"

    # 切换到 V2
    r_switch = client.post_admin("./DSL_script/test2.dsl")
    assert r_switch.status_code == 200

    r1 = client.post_msg(uid, "我要查库存")
    assert "商品编号" in r1.text

    # 中途切回 V1
    r_switch = client.post_admin("./DSL_script/test1.dsl")
    assert r_switch.status_code == 200

    time.sleep(2)

    r2 = client.post_msg(uid, "333153695")

    assert "库存" not in r2.text
    assert ("您好" in r2.text) or ("订单" in r2.text)
