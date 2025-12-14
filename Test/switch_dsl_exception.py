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

    def test_01_invalid_path(self):
        resp_switch = self.send_admin_msg("./DSL_script/test2.dsl")

        logger.info("\n=== Test 01: 错误的 DSL 路径 ===")
        uid="auto_01"

        resp1 = self.send_msg(uid, "你好。")
        self.assertIn("欢迎来到我们的商城", resp1.text, "回复不是预期的问候语")
        
        resp = self.send_admin_msg("./DSL_script/not_exist.dsl")
        self.assertNotEqual(resp.status_code, 200, "DSL 路径错误时，服务器应该返回错误状态码")

        resp3 = self.send_msg(uid, "你好。")
        self.assertIn("欢迎来到我们的商城", resp3.text, "传递 dsl路径 错误时，dsl 被更改")

    def test_02_missing_path(self):
        logger.info("\n=== Test 02: 缺少 DSL 路径 ===")
        uid="auto_02"

        resp1 = self.send_msg(uid, "你好。")
        self.assertIn("欢迎来到我们的商城", resp1.text, "回复不是预期的问候语")
        
        resp2 = self.send_admin_msg("")
        self.assertNotEqual(resp2.status_code, 200, "缺少 DSL 路径时，服务器应该返回错误状态码")

        resp3 = self.send_msg(uid, "你好。")
        self.assertIn("欢迎来到我们的商城", resp3.text, "传递 dsl路径 为空时，dsl 被更改")

    def test_03_less_valid_dsl_file(self):
        logger.info("\n=== Test 03: 轻微错误的 DSL 文件 ===")
        uid="auto_03"

        resp1 = self.send_msg(uid, "你好。")
        self.assertIn("欢迎来到我们的商城", resp1.text, "回复不是预期的问候语")
        
        resp2 = self.send_admin_msg("./DSL_script/less_valid.dsl")
        self.assertEqual(resp2.status_code, 500, "接受了错误的文件")

    def test_04_invalid_dsl_file1(self):
        logger.info("\n=== Test 04: 错误的 DSL 文件1 未知类或者方法的调用 ===")
        uid="auto_04"

        resp1 = self.send_msg(uid, "你好。")
        self.assertIn("欢迎来到我们的商城", resp1.text, "回复不是预期的问候语")
        
        resp2 = self.send_admin_msg("./DSL_script/invalid1.dsl")
        self.assertEqual(resp2.status_code, 500, "接受了错误的文件")

    def test_05_invalid_dsl_file2(self):
        logger.info("\n=== Test 05: 错误的 DSL 文件2 关键字错误 ===")
        uid="auto_05"

        resp1 = self.send_msg(uid, "你好。")
        self.assertIn("欢迎来到我们的商城", resp1.text, "回复不是预期的问候语")
        
        resp2 = self.send_admin_msg("./DSL_script/invalid2.dsl")
        self.assertEqual(resp2.status_code, 500, "接受了错误的文件")

    def test_06_invalid_dsl_file3(self):
        logger.info("\n=== Test 06: 错误的 DSL 文件3 参数数量不正确 ===")
        uid="auto_06"

        resp1 = self.send_msg(uid, "你好。")
        self.assertIn("欢迎来到我们的商城", resp1.text, "回复不是预期的问候语")
        
        resp2 = self.send_admin_msg("./DSL_script/invalid3.dsl")
        self.assertEqual(resp2.status_code, 500, "接受了错误的文件")


if __name__ == '__main__':
    logger.info("启动自动化验收测试 (Driver)...")
    unittest.main(verbosity=2,exit=False)