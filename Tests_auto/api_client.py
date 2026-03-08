import requests
import logging
import json
import time

logger = logging.getLogger("TestDriver")

class BotClient:
    def __init__(self, base_url="http://localhost:8080"):
        self.base_url = base_url.rstrip('/')
        self.session = requests.Session()

    def _log_request(self, method, url, headers, data):
        logger.info(f"------------------------------------------------------")
        logger.info(f"[REQUEST] {method} {url}")
        if headers:
            logger.debug(f"   Headers: {headers}")
        logger.info(f"   Payload: {data}")

    def _log_response(self, response, duration):
        logger.info(f"[RESPONSE] Status: {response.status_code} | Time: {duration:.2f}ms")
        try:
            content = json.dumps(response.json(), ensure_ascii=False)
        except:
            content = response.text.strip()
        logger.info(f"   Body   : {content}")
        logger.info(f"------------------------------------------------------\n")

    def post_msg(self, user_id, text, timeout=10):
        url = f"{self.base_url}/"
        headers = {
            "X-User-ID": user_id,
            "Content-Type": "text/plain; charset=utf-8"
        }
        
        self._log_request("POST", url, headers, text)
        
        start = time.time()
        try:
            resp = self.session.post(url, data=text.encode('utf-8'), headers=headers, timeout=timeout)
            duration = (time.time() - start) * 1000
            self._log_response(resp, duration)
            return resp
        except Exception as e:
            logger.error(f"❌ Request Failed: {e}")
            raise e

    def post_admin(self, dsl_path, timeout=10):
        url = f"{self.base_url}/admin"
        self._log_request("POST", url, None, dsl_path)
        
        start = time.time()
        try:
            resp = self.session.post(url, data=dsl_path.encode('utf-8'), timeout=timeout)
            duration = (time.time() - start) * 1000
            self._log_response(resp, duration)
            return resp
        except Exception as e:
            logger.error(f"❌ Admin Request Failed: {e}")
            raise e