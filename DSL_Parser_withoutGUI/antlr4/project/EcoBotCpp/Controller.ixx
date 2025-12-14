module;
#include "EcoBotParser.h"
#include "EcoBotLexer.h"
#include "drogon/drogon.h"

export module Controller;
import EcoBotInterpreter;
import IntentRecognition;
import Context;
import ValidateVisitor;

struct DSLResources {
	std::unique_ptr<std::ifstream> fileStream;
	std::unique_ptr<antlr4::ANTLRInputStream> input;
	std::unique_ptr<EcoBotLexer> lexer;
	std::unique_ptr<antlr4::CommonTokenStream> tokens;
	std::unique_ptr<EcoBotParser> parser;
	EcoBotParser::ProgramContext* tree = nullptr;

	std::vector<std::string> intents;
	std::vector<std::string> keywords;
};
static std::atomic<std::shared_ptr<DSLResources>> g_dsl_ptr;

struct UserSession {
	std::mutex mtx;
	Context ctx;
	std::string lastTimeIntent;
	std::set<std::string> missingSlot;
};
static std::map<std::string, std::shared_ptr<UserSession>> g_sessions;
static std::shared_mutex g_session_mtx;

std::shared_ptr<DSLResources> loadDSLInternal(const std::string& scriptPath)
{
	auto data{ std::make_shared<DSLResources>() };

	data->fileStream = std::make_unique<std::ifstream>(scriptPath);

	if (!data->fileStream->is_open()) {
		LOG_ERROR << "Fatal Error: Cannot open DSL script: " << scriptPath;
		return nullptr;
	}

	data->input = std::make_unique<antlr4::ANTLRInputStream>(*data->fileStream);
	data->lexer = std::make_unique<EcoBotLexer>(data->input.get());
	data->tokens = std::make_unique<antlr4::CommonTokenStream>(data->lexer.get());
	data->parser = std::make_unique<EcoBotParser>(data->tokens.get());

	data->tree = data->parser->program();

	//检查语法错误
	if (data->parser->getNumberOfSyntaxErrors() > 0) {
		LOG_ERROR << "Fatal Error: Syntax errors found in DSL script: " << scriptPath;
		return nullptr;
	}

	// 检查dsl中的类，方法和参数是否正确
	ValidatorVisitor validator;
	try {
		validator.visit(data->tree); 
		LOG_INFO << "脚本无语法错误，通过静态测试。";
	}
	catch (const std::exception& e) {
		LOG_ERROR << "脚本存在错误： " << e.what();
		return nullptr;
	}


	for (auto* intent : data->tree->intentDef()) {
		std::string intentName{ intent->ID()->getText() };
		data->intents.push_back(intentName);
		for (auto* stmt : intent->stmtList()->stmt()) {
			if (stmt->requireStmt()) {
				auto* reqCtx{ stmt->requireStmt() };
				std::string keyword{ reqCtx->ID()->getText() };
				data->keywords.push_back(keyword);
			}
			else if (stmt->callStmt()) {
				auto* callCtx{ stmt->callStmt() };
				if (callCtx->ID()) {
					std::string keyword{ callCtx->ID()->getText() };
					data->keywords.push_back(keyword);
				}
			}
		}
	}

	return data;
}
export bool initOrReloadDSL(const std::string& scriptPath)
{
	auto newDSL = loadDSLInternal(scriptPath);
	if (newDSL) {
		g_dsl_ptr.store(newDSL);
		LOG_INFO << "脚本初始化/更换完成";
		return true;
	}
	else {
		LOG_ERROR << "脚本加载失败，保持原样";
		return false;
	}
}

//export std::string web_running(std::string userId,std::string userInput)
//{
//	std::shared_ptr<DSLResources> l_dsl_ptr{ g_dsl_ptr.load() };
//
//	EcoBotParser::IntentDefContext* targetNode{ nullptr };
//	std::string finalIntent;
//
//	auto [iter, isNew] {g_sessions.try_emplace(userId)};
//	
//	UserSession& session{ iter->second };
//
//	if (isNew) {
//		session.ctx.add("user_id", userId);
//	}
//
//	//LLM 识别
//	initPrompt(l_dsl_ptr->intents, l_dsl_ptr->keywords,session.lastTimeIntent,session.missingSlot);
//	NLUResult result{ llmNLU(userInput) };
//	for (const auto& [key, value] : result.entities) {
//		session.ctx.add(key, value);
//		LOG_INFO<< "根据LLM识别自动预填槽位: " << key << " = " << value;
//	}
//	finalIntent = result.intent;
//
//	//判断槽位是否填充
//	if (!session.missingSlot.empty()) {
//		for (auto it{ result.entities.begin() }; it != result.entities.end();it++) {
//			session.missingSlot.erase(it->first);
//		}
//	}
//
//	//查找意图
//	for (auto* intentCtx : l_dsl_ptr->tree->intentDef()) {
//		if (intentCtx->ID()->getText() == finalIntent) {
//			targetNode = intentCtx;
//			break;
//		}
//	}
//	if (!targetNode) {
//		//老实说，这个部分不会用到的，毕竟会返回默认意图
//		session.lastTimeIntent = "";
//		return "我不知道该怎么处理这个意图";
//	}
//	else {
//		LOG_INFO<< "最后确定的意图是：" << finalIntent;
//	}
//	session.lastTimeIntent = finalIntent;
//
//	//真正进入意图并读取回复
//	EcoBotInterpreter interpreter(session.ctx);
//	try {
//		interpreter.visit(targetNode);
//		session.ctx.clear();
//
//	}
//	catch (const MissingSlotException&e) {
//		session.missingSlot.insert(e.varName);
//	}
//
//	//最后返回输出
//	return interpreter.getOutput(); 
//}

export drogon::Task<std::string> async_web_running(std::string userId, std::string userInput)
{
	std::shared_ptr<DSLResources> l_dsl_ptr{ g_dsl_ptr.load() };
	if (!l_dsl_ptr) 
		co_return "系统正在初始化，请稍后...";

	//找用户上下文，读锁和写锁；提前拷贝NLU需要的数据
	std::shared_ptr<UserSession> session{ nullptr };
	std::string lastIntentCopy;
	std::set<std::string> missingSlotCopy;

	{
		{
			std::shared_lock<std::shared_mutex> session_lock(g_session_mtx);
			auto it{ g_sessions.find(userId) };
			if (it != g_sessions.end()) {
				session = it->second;
			}
		}
		if (!session) {
			std::unique_lock<std::shared_mutex>session_write_lock(g_session_mtx);
			auto it = g_sessions.find(userId);
			if (it == g_sessions.end()) {
				session = std::make_shared<UserSession>();
				session->ctx.add("user_id", userId);
				g_sessions[userId] = session;
			}
			else {
				session = it->second;
			}
		}

		{
			std::lock_guard<std::mutex> userLock(session->mtx);
			lastIntentCopy = session->lastTimeIntent;
			missingSlotCopy = session->missingSlot;
		}

	}

	//使用协程，LLM 识别
	//先检测是否更新了dsl，如果是，需要刷新lastTimeIntent和slots
	auto it{ std::find(l_dsl_ptr->intents.begin(),l_dsl_ptr->intents.end(),lastIntentCopy)};

	if (it == l_dsl_ptr->intents.end()) {
		lastIntentCopy = "";
		missingSlotCopy.clear();
	}

	NLUResult result{ co_await llmNLU(userInput,l_dsl_ptr->intents, l_dsl_ptr->keywords, lastIntentCopy, missingSlotCopy) };

	//检查一下用户输入是不是过长
	std::string tip;
	std::string safeInput;
	if (userInput.length() > 200) {
		safeInput = std::string(userInput.substr(0, 200));
		LOG_WARN << "用户输入太长截断了。";
		tip = "（您的输入超过200字，被截断了一部分，回复可能不准确）";
	}

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
		//老实说，这个部分不会用到的，毕竟会返回默认意图
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

	co_return interpreter.getOutput()+tip;
}