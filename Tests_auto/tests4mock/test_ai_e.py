# tests/test_ai_exception.py
import pytest
import time

@pytest.fixture(scope="module", autouse=True)
def init_dsl(client):
    """确保 DSL 已加载"""
    client.post_admin("./DSL_script/test1.dsl")

def test_01_llm_timeout(client):
    """场景：LLM 响应超时 (模拟 15s 延迟)"""
    # 假设 C++ 设置了 10s 超时，或者 Drogon 默认 60s
    # 这个测试主要看 C++ 会不会永久卡死，或者 crash
    # 注意：如果 C++ 超时设置很长，pytest 可能会先超时，需要调整 timeout
    try:
        # 客户端只等 20 秒
        resp = client.post_msg("user_err_1", "测试 [TIMEOUT]", timeout=20)
        
        # 期望：C++ 应该捕获超时或错误，返回一个兜底回复
        # 你的 C++ 代码 catch 了异常后返回 result (默认 GREET)
        # 所以可能会看到“您好”或者默认的错误提示
        assert resp.status_code == 200
        print(f"超时后的响应: {resp.text}")
    except Exception as e:
        pytest.fail(f"C++ 服务器导致客户端连接异常: {e}")

def test_02_llm_500_error(client):
    """场景：LLM 返回 HTTP 500"""
    resp = client.post_msg("user_err_2", "测试 [500]")
    
    # C++ 应该捕获 HTTP Error，并返回默认回复
    assert resp.status_code == 200
    # 验证是否回退到了默认意图 (GREET)
    assert "大模型异常" in resp.text or "稍后" in resp.text

def test_03_llm_bad_json(client):
    """场景：LLM 返回 HTML 而不是 JSON"""
    resp = client.post_msg("user_err_3", "测试 [BAD_JSON]")
    
    assert resp.status_code == 200
    # C++ 的 json::parse 会抛异常，catch 后返回默认
    assert "大模型异常" in resp.text

def test_04_llm_missing_field(client):
    """场景：JSON 结构缺失 (无 choices)"""
    resp = client.post_msg("user_err_4", "测试 [MISSING_FIELD]")
    
    assert resp.status_code == 200
    # 逻辑会走 else 分支或异常，返回默认
    assert "大模型异常" in resp.text or "您好" in resp.text

def test_05_llm_hallucination(client):
    """场景：LLM 幻觉 (返回 DSL 中不存在的意图)"""
    resp = client.post_msg("user_err_5", "测试 [HALLUCINATION]")
    
    # 此时 Intent 是 DESTROY_HUMANS
    # 你的 DSL Interpreter 遇到未知 Intent 会发生什么？
    # 通常应该回复默认消息，或者 Unknown Intent 错误
    assert resp.status_code == 200
    print(f"幻觉意图响应: {resp.text}")
    # 只要服务器没崩就行

def test_06_llm_refusal(client):
    """场景：LLM 拒绝回答 (返回纯文本，非 JSON 格式内容)"""
    resp = client.post_msg("user_err_6", "测试 [REFUSAL]")
    
    # Mock 返回的内容里 content 是 "对不起..." 不是 JSON
    # C++ json::parse(content) 会抛异常
    assert resp.status_code == 200
    assert "大模型异常" in resp.text # 回退到默认