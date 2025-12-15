module;
#include "drogon/drogon.h"

export module ChatService;
import DSLManager;
import SessionManager;
import IntentRecognition;
import EcoBotInterpreter;

export class ChatService
{
private:
	ChatService() {}
	DSLManager dslManager;
	SessionManager sessionManager;
	IntentRecognition intentRecognition;
public:
	static ChatService& instance() {
		static ChatService inst;
		return inst;
	}
	ChatService(const ChatService&) = delete;
	ChatService& operator=(const ChatService&) = delete;
	drogon::Task<std::string> handleInput(std::string userId, std::string userInput);
	std::expected<void, std::string> initOrReloadDSL(const std::string& scriptPath);
};

//implementations

drogon::Task<std::string> ChatService::handleInput(std::string userId, std::string userInput)
{
	//获取dsl指针
	std::shared_ptr<DSLResources> l_dsl_ptr{ dslManager.loadDSLPtr()};
	if (!l_dsl_ptr)
		co_return "系统正在初始化，请稍后...";

	//获取用户上下文
	//读锁和写锁；提前拷贝NLU需要的数据
	std::shared_ptr<UserSession> session{ sessionManager.getOrCreateUserSession(userId)};
	std::string lastIntentCopy;
	std::set<std::string> missingSlotCopy;

	{
		std::lock_guard<std::mutex> userLock(session->mtx);
		lastIntentCopy = session->lastTimeIntent;
		missingSlotCopy = session->missingSlot;
	}

	//使用协程，LLM 识别
	//先检测是否更新了dsl，如果是，需要刷新lastTimeIntent和slots
	auto it{ std::find(l_dsl_ptr->intents.begin(),l_dsl_ptr->intents.end(),lastIntentCopy) };

	if (it == l_dsl_ptr->intents.end()) {
		lastIntentCopy = "";
		missingSlotCopy.clear();
	}

	//检查一下用户输入是不是过长
	std::string tip;
	std::string safeInput;
	if (userInput.length() > 200) {
		safeInput = std::string(userInput.substr(0, 200));
		LOG_WARN << "用户输入太长截断了。";
		tip = "（您的输入超过200字，被截断了一部分，回复可能不准确）";
	}
	else {
		safeInput = userInput;
	}

	NLUResult result{ co_await intentRecognition.llmNLU(safeInput,l_dsl_ptr->intents, l_dsl_ptr->keywords, lastIntentCopy, missingSlotCopy) };

	//根据LLM结果 预填槽位，更新意图，更新缺失槽位
	std::lock_guard<std::mutex> userLock(session->mtx);

	for (const auto& [key, value] : result.entities) {
		session->ctx.add(key, value);
		LOG_INFO << "根据LLM识别自动预填槽位: " << key << " = " << value;
	}
	std::string finalIntent{ result.intent };

	if (!session->missingSlot.empty()) {
		for (auto it{ result.entities.begin() }; it != result.entities.end(); it++) {
			session->missingSlot.erase(it->first);
		}
	}

	//查找意图
	EcoBotParser::IntentDefContext* targetNode{ nullptr };
	for (auto* intentCtx : l_dsl_ptr->tree->intentDef()) {
		if (intentCtx->ID()->getText() == finalIntent) {
			targetNode = intentCtx;
			break;
		}
	}
	if (!targetNode) {
		session->lastTimeIntent = "";
		co_return "我不知道该怎么处理这个意图，您的输入可能包含非法信息。";
	}
	else {
		LOG_INFO << "最后确定的意图是：" << finalIntent;
		session->lastTimeIntent = finalIntent;
	}

	//执行：真正进入意图并读取回复
	EcoBotInterpreter interpreter(session->ctx);
	try {
		interpreter.visit(targetNode);
		session->ctx.clear();

	}
	catch (const MissingSlotException& e) {
		session->missingSlot.insert(e.varName);
	}
	catch (const std::exception& e) {
		LOG_ERROR << "System Crash: " << e.what();
		co_return "系统繁忙，遇到了一点技术问题，请稍后重试。";
	}

	co_return interpreter.getOutput() + tip;
}
std::expected<void,std::string> ChatService::initOrReloadDSL(const std::string& scriptPath)
{
	return dslManager.initOrReloadDSL(scriptPath);
}