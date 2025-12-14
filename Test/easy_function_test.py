import unittest
import requests
import time
import logging

logging.basicConfig(level=logging.CRITICAL, format='%(asctime)s %(levelname)s %(message)s')
logger = logging.getLogger(__name__)

API_URL = "http://localhost:8080/"

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

    def test_01_easy_reply(self):
        logger.info("\n=== Test 01: 验证简单回复 ===")
        uid = "auto_01"
        
        resp = self.send_msg(uid, "你好。")
        
        self.assertEqual(resp.status_code, 200)
        self.assertIn("您好", resp.text, "回复不是预期的问候语")

    def test_02_unknown_intent(self):
        logger.info("\n=== Test 02: 未知意图 ===")
        uid = "auto_02"

        resp = self.send_msg(uid, "今天天气怎么样？")
        
        self.assertEqual(resp.status_code, 200)
        self.assertIn("您好", resp.text, "回复不是默认的问候语")
        
    def test_03_long_intent(self):

        logger.info("\n=== Test 03: 简单长意图 ===")
        uid = "auto_03"
        
        resp1 = self.send_msg(uid, "我想查一下订单状态")
        self.assertIn("请提供您的订单号", resp1.text, "机器人没有触发缺槽位追问")

        resp2 = self.send_msg(uid, "订单号是3330")

        self.assertIn("已发货", resp2.text, "长意图执行失败或订单状态不正确")

    def test_04_auto_slot(self):

        logger.info("\n=== Test 04: 自动填槽 ===")
        uid = "auto_04"
        
        resp1 = self.send_msg(uid, "我想查一下订单状态，订单号是3331")
        self.assertNotIn("请提供您的订单号", resp1.text, "机器人不应该触发缺槽位追问")
        self.assertIn("已签收", resp1.text, "订单状态不正确或长意图执行失败")

    def test_05_long_intent_2(self):

        logger.info("\n=== Test 05: 长意图 ===")
        uid = "auto_05"
        
        resp1 = self.send_msg(uid, "我想要退款订单")
        self.assertIn("哪个订单", resp1.text, "机器人没有触发缺槽位追问")
        resp2 = self.send_msg(uid, "订单号是3330")
        self.assertIn("退款原因", resp2.text, "机器人没有触发第二次缺槽位追问")
        resp3 = self.send_msg(uid, "商品有问题")
        self.assertIn("已提交", resp3.text, "返回结果不正确或长意图执行失败")

    def test_06_auto_slot_2(self):

        logger.info("\n=== Test 06: 自动填槽 ===")
        uid = "auto_06"
        
        resp1 = self.send_msg(uid, "我想要退款订单，订单号是3331，退款原因是商品降价了")
        self.assertNotIn("哪个订单", resp1.text, "机器人不应该触发缺槽位追问")
        self.assertNotIn("退款原因", resp1.text, "机器人不应该触发第二次缺槽位追问")
        self.assertIn("失败", resp1.text, "返回结果不正确或长意图执行失败")

if __name__ == '__main__':
    logger.info("启动自动化验收测试 (Driver)...")
    unittest.main(verbosity=2,exit=False)