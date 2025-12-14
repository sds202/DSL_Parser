import unittest
import requests
import time
import logging

logging.basicConfig(level=logging.CRITICAL, format='%(asctime)s %(levelname)s %(message)s')
logger = logging.getLogger(__name__)

API_URL = "http://localhost:8080/"
ADMIN_URL = "http://localhost:8080/admin"

class TestChatBot(unittest.TestCase):
    def setUp(self):
        self.session = requests.Session()

    def send_msg(self, user_id, text):
        headers = {
            "X-User-ID": user_id,         
            "Content-Type": "text/plain; charset=utf-8" 
        }
        
        try:
            start_time = time.time()
            response = self.session.post(
                API_URL, 
                data=text.encode('utf-8'), 
                headers=headers,
                timeout=10
            )
            duration = (time.time() - start_time) * 1000

            logger.info(" [User: %s] 发送: %s", user_id, text)
            logger.info("    -> 耗时: %.0fms | 回复: %s", duration, response.text.strip())
            
            return response
        except requests.exceptions.RequestException as e:
            self.fail(f"请求失败，请检查服务器是否启动: {e}")

    def send_admin_msg(self, text):
        admin_url = ADMIN_URL
        try:
            response = requests.post(admin_url, data=text.encode('utf-8'))
            return response
        except requests.exceptions.RequestException as e:
            self.fail(f"Admin 请求失败，请检查服务器是否启动: {e}")

    def test_01_dsl_switch(self):
        logger.info("\n=== Test 01: DSL 热更新功能验证 ===")
        uid = "auto_01"

        # 验证 dsl V1 正常
        resp1 = self.send_msg(uid, "我想查一下订单状态，订单号是3331")
        self.assertNotIn("请提供您的订单号", resp1.text, "机器人不应该触发缺槽位追问")
        self.assertIn("已签收", resp1.text, "订单状态不正确或长意图执行失败")

        # 更换 DSL V2
        resp2 = self.send_admin_msg("./DSL_script/test2.dsl")
        self.assertEqual(resp2.status_code, 200, "DSL 热更新失败")

        # 验证 V2 生效
        resp3 = self.send_msg(uid, "我要使用优惠券，优惠券代码是6660")
        self.assertIn("成功使用", resp3.text, "v2 切换失败 或者 其他错误")

    def test_02_missing_path(self):
        logger.info("\n=== Test 02: 缺少 DSL 路径 ===")
        uid="auto_02"

        resp1 = self.send_msg(uid, "你好。")
        self.assertIn("欢迎来到我们的商城", resp1.text, "回复不是预期的问候语")
        
        resp2 = self.send_admin_msg("")
        self.assertNotEqual(resp2.status_code, 200, "缺少 DSL 路径时，服务器应该返回错误状态码")

        resp3 = self.send_msg(uid, "你好。")
        self.assertIn("欢迎来到我们的商城", resp3.text, "传递 dsl路径 为空时，dsl 被更改")

    def test_03_invalid_path(self):
        logger.info("\n=== Test 03: 错误的 DSL 路径 ===")
        uid="auto_03"

        resp1 = self.send_msg(uid, "你好。")
        self.assertIn("欢迎来到我们的商城", resp1.text, "回复不是预期的问候语")
        
        resp = self.send_admin_msg("./DSL_script/not_exist.dsl")
        self.assertNotEqual(resp.status_code, 200, "DSL 路径错误时，服务器应该返回错误状态码")

        resp3 = self.send_msg(uid, "你好。")
        self.assertIn("欢迎来到我们的商城", resp3.text, "传递 dsl路径 错误时，dsl 被更改")

    def test_04_switch_during_chat(self):
        logger.info("\n=== Test 04: 聊天中途 DSL 切换 ===")
        uid = "auto_04"

        resp1 = self.send_msg(uid, "我要查库存")
        self.assertIn("商品编号", resp1.text, "V2 环境未生效")

        logger.info(">>> 正在中途切换 DSL 到 V1 ...")
        resp_switch = self.send_admin_msg("./DSL_script/test1.dsl")
        self.assertEqual(resp_switch.status_code, 200, "DSL 热更新失败")

        time.sleep(2)

        resp2 = self.send_msg(uid, "333153695")

        self.assertNotIn("库存", resp2.text, "错误：切换 DSL 后仍然执行了旧逻辑")
        logger.info(f"切换后的回复: {resp2.text.strip()}")
        self.assertTrue("您好" in resp2.text or "订单" in resp2.text,"切换 DSL 后，回复不是预期的问候语")


if __name__ == '__main__':
    logger.info("启动自动化验收测试 (Driver)...")
    unittest.main(verbosity=2,exit=False)