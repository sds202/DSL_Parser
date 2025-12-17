import requests
import concurrent.futures
import time
import random
import os
import shutil

# ================= 配置区域 =================
HOST = "http://127.0.0.1:8080"
CHAT_URL = f"{HOST}/"              # 聊天接口
ADMIN_URL = f"{HOST}/admin"        # 管理接口 (用于切换 DSL)

# 本地 DSL 文件存放路径 (对应 C++ 读取的相对路径)
DSL_DIR = "./DSL_script"
DSL_PATH_V1 = f"{DSL_DIR}/concurrent1.dsl"
DSL_PATH_V2 = f"{DSL_DIR}/concurrent2.dsl"

CONCURRENT_USERS = 20              # 并发线程数
TOTAL_SESSIONS = 100               # 总会话数

def set_initial_dsl():
    """初始化服务器使用 V1 版本"""
    print(f"[Init] 请求服务器加载初始 DSL: {DSL_PATH_V1}")
    try:
        # 发送路径字符串给 C++
        resp = requests.post(ADMIN_URL, data=DSL_PATH_V1)
        if resp.status_code == 200:
            print("[Init] 服务器初始化成功")
        else:
            print(f"[Init] 服务器初始化失败: {resp.status_code} - {resp.text}")
            exit(1)
    except Exception as e:
        print(f"[Init] 连接服务器失败，请确认 C++ 程序已启动。错误: {e}")
        exit(1)

def send_chat(user_id, message):
    """发送聊天消息"""
    headers = {"X-User-ID": str(user_id)}
    try:
        # 对应 req->getBody()
        resp = requests.post(CHAT_URL, data=message.encode('utf-8'), headers=headers, timeout=5)
        if resp.status_code == 200:
            return resp.text
        return None
    except Exception:
        return None

def trigger_hot_swap():
    """触发热更新，切换到 V2 文件路径"""
    print(f"\n>>> [ADMIN] 正在通知服务器切换 DSL 文件至: {DSL_PATH_V2} >>>")
    try:
        # 关键点：发送的是文件路径字符串
        resp = requests.post(ADMIN_URL, data=DSL_PATH_V2)
        if resp.status_code == 200:
            print("<<< [ADMIN] 切换指令发送成功！后续回复应变为 V2 <<<")
        else:
            print(f"<<< [ADMIN] 切换失败: {resp.status_code} <<<")
    except Exception as e:
        print(f"<<< [ADMIN] 切换请求异常: {e} <<<")

def run_session_task(user_id):
    """
    模拟单个用户会话任务
    返回: (Success: bool, Version_Tag: str)
    """
    # 1. 触发意图
    reply1 = send_chat(user_id, "查询订单状态")
    if not reply1 or "订单号" not in reply1:
        return False, "Req_Fail"

    # 2. 模拟思考延迟 (制造并发重叠)
    time.sleep(random.uniform(0.01, 0.05))

    # 3. 填槽 (验证内存隔离)
    my_order_id = f"{random.randint(1000, 9999)}{random.randint(1000, 9999)}"
    reply2 = send_chat(user_id, my_order_id)
    
    if not reply2: 
        return False, "Resp_Fail"

    # 4. 验证数据正确性
    if my_order_id not in reply2 and "检测到DSL更新" not in reply2:
        return False, "Slot_Error" # 严重错误：串槽

    # 5. 识别版本
    if "【V1】" in reply2: return True, "V1"
    if "【V2】" in reply2: return True, "V2"
    
    return True, "Unknown"

def main():
    # 1. 准备环境
    set_initial_dsl()
    
    print("\n=== 开始并发压测 (5秒后开始) ===")
    time.sleep(3) # 给服务器一点喘息时间

    results = {"V1": 0, "V2": 0, "Error": 0}
    
    with concurrent.futures.ThreadPoolExecutor(max_workers=CONCURRENT_USERS) as executor:
        futures = []
        
        # --- 阶段 1: 提交前 50% 任务 (预期 V1) ---
        print(f"--- 阶段 1: 模拟 {TOTAL_SESSIONS//2} 个用户对话 ---")
        for i in range(TOTAL_SESSIONS // 2):
            futures.append(executor.submit(run_session_task, f"user_A_{i}"))
        
        # --- 阶段 2: 运行时热更新 ---
        time.sleep(3) # 等待部分任务运行中
        trigger_hot_swap() # 切换 DSL
        
        # --- 阶段 3: 提交后 50% 任务 (预期 V2) ---
        print(f"--- 阶段 3: 模拟剩余 {TOTAL_SESSIONS - TOTAL_SESSIONS//2} 个用户对话 ---")
        for i in range(TOTAL_SESSIONS // 2, TOTAL_SESSIONS):
            futures.append(executor.submit(run_session_task, f"user_B_{i}"))
            
        # --- 收集结果 ---
        for future in concurrent.futures.as_completed(futures):
            success, tag = future.result()
            if success:
                if tag in results: results[tag] += 1
                else: results["Error"] += 1
            else:
                results["Error"] += 1
                print(f"[Failure Type] {tag}")

    print("\n========= 测试总结 =========")
    print(f"V1 回复数量: {results['V1']}")
    print(f"V2 回复数量: {results['V2']}")
    print(f"失败/错误数: {results['Error']}")
    
    if results['Error'] == 0 and results['V1'] > 0 and results['V2'] > 0:
        print("\nSUCCESS: 成功演示了动态 DSL 切换与并发会话隔离！")
    else:
        print("\nWARNING: 请检查是否有失败请求或版本切换未生效。")

if __name__ == "__main__":
    main()
