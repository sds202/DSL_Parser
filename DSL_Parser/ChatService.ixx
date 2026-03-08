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

	std::string tipReloadDSL;

	//获取用户上下文
	//读锁和写锁；提前拷贝NLU需要的数据
	std::shared_ptr<UserSession> session{ sessionManager.getOrCreateUserSession(userId)};
	std::string lastIntentCopy;
	std::set<std::string> missingSlotCopy;

	{
		std::lock_guard<std::mutex> userLock(session->mtx);

		LOG_DEBUG << "v" << session->currentDslVersion << " -> v" << l_dsl_ptr->version;

		if (session->currentDslVersion != l_dsl_ptr->version) {
			tipReloadDSL = (session->currentDslVersion==0)?"":"（检测到DSL更新，您的对话可能受影响）";
			LOG_INFO << "检测到 DSL 版本变更 (v" << session->currentDslVersion
				<< " -> v" << l_dsl_ptr->version << ")，正在检查兼容性...";
			session->currentDslVersion = l_dsl_ptr->version;

			//需要做全面检查
			if (!session->lastTimeIntent.empty()) {



				bool isCompatible{ false };

				//检查意图是否存在
				auto intentIt = std::find(l_dsl_ptr->intents.begin(), l_dsl_ptr->intents.end(), session->lastTimeIntent);

				if (intentIt != l_dsl_ptr->intents.end()) {
					//检查槽位是否兼容
					bool slotsCompatible = true;
					for (const auto& slot : session->missingSlot) {
						if (!l_dsl_ptr->hasSlot(session->lastTimeIntent, slot)) {
							slotsCompatible = false;
							break;
						}
					}
					if (slotsCompatible) isCompatible = true;
				}

				//如果不兼容，重置状态
				if (!isCompatible) {
					LOG_WARN << "版本不兼容，重置用户 " << userId << " 的会话状态。";
					session->lastTimeIntent.clear();
					session->missingSlot.clear();
				}
				else {
					LOG_INFO << "版本兼容，用户状态已平滑迁移。";
				}
			}
		}
		lastIntentCopy = session->lastTimeIntent;
		missingSlotCopy = session->missingSlot;
	}

	//使用协程，LLM 识别
	
	////先检测是否更新了dsl，如果是，需要刷新lastTimeIntent和slots
	//auto it{ std::find(l_dsl_ptr->intents.begin(),l_dsl_ptr->intents.end(),lastIntentCopy) };

	//std::string tipReloadDSL;
	//if (it == l_dsl_ptr->intents.end()) {
	//	lastIntentCopy = "";
	//	missingSlotCopy.clear();
	//	tipReloadDSL = "（检测到DSL更新，您的对话可能受影响）";
	//}


	//检查一下用户输入是不是过长
	std::string tipToLong;
	std::string safeInput;
	if (userInput.length() > 200) {
		safeInput = std::string(userInput.substr(0, 200));
		LOG_WARN << "用户输入太长截断了。";
		tipToLong = "（您的输入超过200字，被截断了一部分，回复可能不准确）";
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

	if (result.serverError) {
		session->ctx.clear();
		co_return "大模型异常，请稍后再试";
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

	co_return interpreter.getOutput() + tipReloadDSL + tipToLong;
}
std::expected<void,std::string> ChatService::initOrReloadDSL(const std::string& scriptPath)
{
	return dslManager.initOrReloadDSL(scriptPath);
}