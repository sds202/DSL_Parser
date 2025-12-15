import json
import random
from locust import HttpUser, task, between, events

# 如果你要测试上传 DSL，请在同目录下放一个 valid.dsl
DSL_FILE_PATH = "valid.dsl"
# 如果没有文件，脚本会自动创建一个假的
try:
    with open(DSL_FILE_PATH, "w", encoding="utf-8") as f:
        f.write('intent TEST { reply "ok"; }')
except:
    pass

class EcoBotUser(HttpUser):
    # 模拟用户思考时间：0.1秒 ~ 0.5秒之间 (高频轰炸)
    # 如果想测极限 QPS，可以设为 constant(0)
    wait_time = between(0.1, 0.5)

    # 这里的权重(weight)决定了任务执行的频率
    # weight=20: 绝大多数时候都在聊天
    @task(20)
    def chat_query_order(self):
        # 构造请求体
        payload = {
            "user_id": "test_user_" + str(random.randint(1, 1000)),
            "message": "我要查订单" # 你的 Mock NLU 应该能识别这个
        }
        headers = {'Content-Type': 'application/json'}

        # 发起 POST 请求
        with self.client.post("/api/chat", data=json.dumps(payload), headers=headers, catch_response=True) as response:
            try:
                # 1. 基础连接检查
                if response.status_code != 200:
                    response.failure(f"HTTP Status {response.status_code}: {response.text}")
                    return

                # 2. 解析 JSON
                res_json = response.json()
                
                # 3. 业务逻辑校验 (根据你的实际 Mock 返回值修改)
                # 假设你的 Mock NLU 返回结果里包含 reply 字段
                reply_text = res_json.get("reply", "")
                
                # 如果回复为空，或者是系统报错，标记为失败
                if not reply_text:
                    response.failure("Reply is empty")
                elif "系统繁忙" in reply_text:
                    # 如果你的后端 catch 到异常返回了这个，说明压测把后端压崩了
                    response.failure("Server Logic Crash (System Busy)")
                else:
                    # 一切正常
                    response.success()

            except json.JSONDecodeError:
                response.failure("Response is not valid JSON")
            except Exception as e:
                response.failure(f"Validation Error: {str(e)}")

    # weight=1: 偶尔（约 1/21 的概率）触发一次 DSL 更新
    # 用于测试热更新是否会导致服务器崩溃或阻塞
    @task(1)
    def reload_dsl_script(self):
        try:
            with open(DSL_FILE_PATH, 'rb') as f:
                files = {'file': f}
                # 假设你的上传接口是这个，不需要校验太多，只要 200 就行
                self.client.post("/api/upload_dsl", files=files, name="/api/upload_dsl (Admin)")
        except Exception as e:
            print(f"File upload failed locally: {e}")
