from flask import Flask, request, jsonify
import json
import re
import logging
import time # 必须引入

app = Flask(__name__)

# 日志配置
log = logging.getLogger('werkzeug')
log.setLevel(logging.ERROR)
logging.basicConfig(level=logging.INFO, format='%(asctime)s - [Mock] %(message)s')

@app.route('/api/paas/v4/chat/completions', methods=['POST'])
def mock_chat_completion():
    try:
        # --- 1. 统一解析请求 (只解析一次) ---
        data = request.get_json(force=True)
        messages = data.get('messages', [])
        
        user_input = next((m['content'] for m in messages if m['role'] == 'user'), "")
        sys_prompt = next((m['content'] for m in messages if m['role'] == 'system'), "")
        
        logging.info(f"收到请求: {user_input}")

        # ================= 故障注入区域 (Fault Injection) =================
        # 如果命中故障关键词，直接返回，不再执行后续正常逻辑

        # 1. 模拟超时
        if "[TIMEOUT]" in user_input:
            logging.info("⚡ 触发模拟: 超时 (Sleep 15s)")
            time.sleep(15)
            return jsonify({"error": "Late Response"}), 200

        # 2. 模拟 HTTP 500
        if "[500]" in user_input:
            logging.info("⚡ 触发模拟: HTTP 500 Error")
            return "Internal Server Error", 500

        # 3. 模拟 HTTP 429
        if "[429]" in user_input:
            logging.info("⚡ 触发模拟: HTTP 429 Too Many Requests")
            return jsonify({"error": { "code": "1301", "message": "Rate limit exceeded"}}), 429

        # 4. 模拟返回非 JSON (HTML)
        if "[BAD_JSON]" in user_input:
            logging.info("⚡ 触发模拟: 返回 HTML/Text")
            return "<html><body>404 Not Found</body></html>", 200

        # 5. 模拟 JSON 结构缺失
        if "[MISSING_FIELD]" in user_input:
            logging.info("⚡ 触发模拟: JSON 结构缺失")
            return jsonify({"status": "ok", "usage": {"total_tokens": 5}}), 200

        # 6. 模拟幻觉
        if "[HALLUCINATION]" in user_input:
            logging.info("⚡ 触发模拟: 未知意图")
            fake_json = json.dumps({"intent": "DESTROY_HUMANS", "entities": {}}, ensure_ascii=False)
            return jsonify({
                "choices": [{"message": {"role": "assistant", "content": fake_json}}]
            })

        # 7. 模拟拒绝回答
        if "[REFUSAL]" in user_input:
            logging.info("⚡ 触发模拟: LLM 拒绝/胡言乱语")
            return jsonify({
                "choices": [{"message": {"role": "assistant", "content": "对不起，作为一个人工智能助手，我不能回答这个问题。"}}]
            })

        # ================= 正常逻辑区域 (Normal Logic) =================
        
        # --- A. 解析 System Prompt ---
        last_intent = "UNKNOWN"
        valid_intents = []

        ctx_match = re.search(r"用户上一次的意图是：([A-Z_]+)", sys_prompt)
        if ctx_match:
            last_intent = ctx_match.group(1)

        intents_match = re.search(r"意图：\[(.*?)\]", sys_prompt)
        if intents_match:
            valid_intents = intents_match.group(1).strip().split()

        # 丢弃无效意图
        if last_intent != "UNKNOWN" and valid_intents and (last_intent not in valid_intents):
            last_intent = "UNKNOWN"

        # --- B. 实体提取 (预处理) ---
        entities = {}
        num_match = re.search(r"(\d+)", user_input)
        number = num_match.group(1) if num_match else None

        # --- C. 意图识别 ---
        intent = "UNKNOWN"

        # 策略 1: 强上下文保护
        context_kept = False
        if last_intent == "REFUND":
            reason_keywords = ["坏", "不喜欢", "降价", "问题", "质量", "原因", "因为"]
            if number or any(k in user_input for k in reason_keywords):
                intent = "REFUND"
                context_kept = True

        # 策略 2: 显式关键词
        if not context_kept:
            if not user_input.strip():
                intent = "GREET"
            elif any(x in user_input for x in ["你好", "您好"]):
                intent = "GREET"
            elif "退款" in user_input:
                intent = "REFUND"
            elif "库存" in user_input:
                intent = "PRODUCT_STOCK_QUERY"
            elif "优惠券" in user_input:
                intent = "APPLY_COUPON"
            elif "活动" in user_input:
                intent = "CONSULT_PROMOTION"
            elif any(x in user_input for x in ["查", "订单"]):
                intent = "QUERY_ORDER"

        # 策略 3: 隐式继承
        if intent == "UNKNOWN":
            if last_intent != "UNKNOWN":
                intent = last_intent
            elif number:
                if "QUERY_ORDER" in valid_intents:
                    intent = "QUERY_ORDER"
                elif "PRODUCT_STOCK_QUERY" in valid_intents:
                    intent = "PRODUCT_STOCK_QUERY"

        # --- D. 实体分配 ---
        if number:
            if intent in ["QUERY_ORDER", "REFUND"]:
                entities["order_id"] = number
            elif intent == "PRODUCT_STOCK_QUERY":
                entities["product_id"] = number
            elif intent == "APPLY_COUPON":
                entities["coupon_code"] = number

        # --- E. 退款原因提取 (最新修复版) ---
        if intent == "REFUND":
            reason_keywords = ["坏", "不喜欢", "降价", "问题", "质量", "原因", "因为"]
            should_extract = any(k in user_input for k in reason_keywords) or (not number and len(user_input) > 1)
            
            if should_extract:
                clean_text = re.sub(r"\d+", "", user_input)
                # 包含 "我" "想" "要" 的增强清洗
                clean_text = re.sub(r"(我|想|要|退款|订单|原因|是|的|因为|号|，|,|。|\.)", "", clean_text).strip()
                
                if len(clean_text) > 0:
                    entities["reason"] = clean_text

        # --- F. 构造返回 ---
        result_json = json.dumps({"intent": intent, "entities": entities}, ensure_ascii=False)
        logging.info(f"Input: {user_input} | Intent: {intent} | Entities: {entities}")

        return jsonify({
            "choices": [{"message": {"role": "assistant", "content": result_json}}],
            "usage": {"total_tokens": 10}
        })

    except Exception as e:
        logging.error(f"Mock Error: {e}")
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    print("🚀 Full Mock Server (Normal + Fault Injection) running on :8081")
    app.run(host='0.0.0.0', port=8081, threaded=True)