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

    def test_01_unknown_intent(self):
        logger.info("\n=== Test 01: 未知意图 ===")
        uid = "auto_01"
        resp0 = self.send_admin_msg("./DSL_script/test1.dsl")
        self.assertEqual(resp0.status_code, 200, "初始化 DSL 失败")

        resp = self.send_msg(uid, "今天天气怎么样？")
        
        self.assertEqual(resp.status_code, 200)
        self.assertTrue("您好" in resp.text or "不知道" in resp.text, "回复不是默认的问候语")

    def test_02_empty_input(self):
        logger.info("\n=== Test 02: 异常测试 - 空消息 ===")
        uid = "auto_02"
        
        resp = self.send_msg(uid, "")
        
        self.assertEqual(resp.status_code, 200, "服务器处理空消息时不能崩溃")
        logger.info("服务器回复: %s", resp.text)

        self.assertIn("您好", resp.text, "空消息的回复不正确")

    def test_03_missing_header(self):
        logger.info("\n=== Test 03: 异常测试 - 缺失 UserID ===")
        
        try:
            resp = self.session.post(
                API_URL, 
                data="你好".encode('utf-8'),
                headers={"Content-Type": "text/plain; charset=utf-8"},
                timeout=5
            )
            
            if resp.status_code == 200:
                logger.info("服务器自动处理了缺失 ID 的情况")
                self.assertIn("visitor", resp.text, "服务器应该使用默认访客 ID 处理请求")
            else:
                logger.info("服务器正确拒绝了无 ID 请求: %d", resp.status_code)
                self.assertTrue(resp.status_code >= 400)
                
        except Exception as e:
            self.fail(f"请求发送失败: {e}")

    def test_04_huge_payload(self):
        logger.info("\n=== Test 04: 超长文本 ===")
        uid = "auto_04"
        
        huge_text = "测试" * 5000 
        
        resp = self.send_msg(uid, huge_text)
        
        self.assertNotEqual(resp.status_code, 500, "服务器被长文本搞崩了")
        self.assertNotEqual(resp.status_code, 200, "服务器不应该正常处理超长文本")
        logger.info("长文本测试响应码: %d", resp.status_code)

    def test_05_truncated_payload(self):
        logger.info("\n=== Test 05: 需要截断的文本 ===")
        uid = "auto_05"
        
        huge_text = "123456789101234567891012345678910123456789101234567891012345678910123456789101234567891012345678910123456789101234567891012345678910123456789101234567891012345678910123456789101234567891012345678910123456789101234567891012345678910123456789101234567891012345678910123456789101234567891012345678910123456789101234567891012345678910"
        
        resp = self.send_msg(uid, huge_text)

        logger.info("长文本测试响应: %s", resp.text)
        self.assertIn("截断", resp.text, "服务器没有正确处理被截断的长文本")

if __name__ == '__main__':
    logger.info("启动自动化验收测试 (Driver)...")
    unittest.main(verbosity=2,exit=False)