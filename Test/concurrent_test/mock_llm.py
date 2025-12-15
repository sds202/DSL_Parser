from flask import Flask, request, jsonify
import json
import re
import time
import logging
import random

app = Flask(__name__)

# --- 1. 设置日志级别，确保能在控制台看到所有信息 ---
logging.basicConfig(level=logging.DEBUG)

# 配置
MOCK_PORT = 8081
SIMULATE_DELAY = random.uniform(0.5, 3)  # 模拟延迟，单位秒

@app.route('/api/paas/v4/chat/completions', methods=['POST'])
def mock_chat_completion():
    # --- 2. [调试核心] 先打印原始数据，不看这就不知道为什么报 400 ---
    raw_data = request.get_data(as_text=True)
    print(f"\n[DEBUG] 收到原始 HTTP Body:\n{raw_data}\n" + "-"*30)

    # --- 3. 尝试解析 JSON ---
    try:
        # force=True: 即使 Header 没写 application/json 也强行解析
        # silent=False: 解析失败直接抛异常，进入 except
        data = request.get_json(force=True)
    except Exception as e:
        error_msg = f"JSON 解析失败! 原因: {e}\n请检查发送的数据是否符合 JSON 标准（双引号）。"
        print(f"[ERROR] {error_msg}")
        return jsonify({"error": error_msg, "received_raw": raw_data}), 400

    # 解析成功，提取字段
    messages = data.get('messages', [])
    user_input = ""
    for msg in messages:
        if msg.get('role') == 'user':
            user_input = msg.get('content', '')

    print(f"[INFO] 解析成功，用户输入: {user_input}")

    # 模拟延迟
    if SIMULATE_DELAY > 0:
        time.sleep(SIMULATE_DELAY)

    # --- 简单的规则逻辑 (保持不变) ---
    intent = "UNKNOWN"
    entities = {}

    if any(w in user_input for w in ["你好", "hello", "hi", "您好"]):
        intent = "GREET"
    elif any(w in user_input for w in ["查", "订单", "状态"]):
        intent = "QUERY_ORDER"
    else:
        # [修改点]：只匹配纯数字
        # \d{5,} 表示匹配连续 5 位以上的数字，避免匹配到年份等误判
        order_match = re.search(r'(\d{5,})', user_input)
        
        if order_match:
            intent = "QUERY_ORDER"
            # 提取出的纯数字 ID
            entities["order_id"] = order_match.group(1)

    # 构造返回
    inner_content = json.dumps({
        "intent": intent,
        "entities": entities
    }, ensure_ascii=False)

    response = {
        "id": "mock-req-debug",
        "created": int(time.time()),
        "model": "GLM-4-Mock-Debug",
        "choices": [{
            "index": 0,
            "message": {
                "role": "assistant",
                "content": inner_content
            },
            "finish_reason": "stop"
        }],
        "usage": {"total_tokens": 0}
    }

    return jsonify(response)

if __name__ == '__main__':
    print(f"Mock Server (Debug模式) 运行中: http://0.0.0.0:{MOCK_PORT}")
    print("提示: 任何代码修改后服务器会自动重启")
    
    # --- 4. 开启 Flask 的 Debug 模式 ---
    app.run(host='0.0.0.0', port=MOCK_PORT, debug=True, threaded=True)