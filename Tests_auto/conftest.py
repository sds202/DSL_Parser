import pytest
import logging
import os
from datetime import datetime
from api_client import BotClient

# 1. 配置日志
@pytest.fixture(scope="session", autouse=True)
def setup_logging():
    # 创建 logs 目录
    log_dir = os.path.join(os.path.dirname(__file__), "logs")
    os.makedirs(log_dir, exist_ok=True)

    # 生成带时间戳的日志文件名
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    log_file = os.path.join(log_dir, f"test_run_{timestamp}.log")

    # 配置 Logger
    logger = logging.getLogger("TestDriver")
    logger.setLevel(logging.INFO)

    # 文件输出 (详细)
    file_handler = logging.FileHandler(log_file, encoding='utf-8')
    file_formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')
    file_handler.setFormatter(file_formatter)

    # 控制台输出 (简洁)
    console_handler = logging.StreamHandler()
    console_formatter = logging.Formatter('%(message)s') # 控制台只看消息，不看时间戳太乱
    console_handler.setFormatter(console_formatter)

    logger.addHandler(file_handler)
    logger.addHandler(console_handler)

    logger.info(f"测试开始，日志文件: {log_file}")
    yield
    logger.info("测试结束")

# 2. 提供 Client 实例
@pytest.fixture(scope="session")
def client():
    """所有测试用例都可以直接使用这个 client 对象"""
    return BotClient("http://localhost:8080")

# 3. 每次测试前打印用例名
@pytest.fixture(autouse=True)
def log_test_name(request):
    logger = logging.getLogger("TestDriver")
    logger.info(f"执行用例: {request.node.name}")