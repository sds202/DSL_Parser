module;
#include "EcoBotParser.h"
#include "EcoBotLexer.h"
#include "trantor/utils/Logger.h"

export module Controller;
import EcoBotInterpreter;
import IntentRecognition;
import Context;

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
	Context ctx;
	std::string lastTimeIntent;
	std::set<std::string> missingSlot;
};
static std::map<std::string, UserSession> g_sessions;
static std::mutex g_session_mtx;

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

export std::string web_running(std::string userId,std::string userInput)
{
	std::shared_ptr<DSLResources> l_dsl_ptr{ g_dsl_ptr.load() };

	EcoBotParser::IntentDefContext* targetNode{ nullptr };
	std::string finalIntent;

	auto [iter, isNew] {g_sessions.try_emplace(userId)};
	
	UserSession& session{ iter->second };

	if (isNew) {
		session.ctx.add("user_id", userId);
	}

	//LLM 识别
	initPrompt(l_dsl_ptr->intents, l_dsl_ptr->keywords,session.lastTimeIntent,session.missingSlot);
	NLUResult result{ llmNLU(userInput) };
	for (const auto& [key, value] : result.entities) {
		session.ctx.add(key, value);
		LOG_INFO<< "根据LLM识别自动预填槽位: " << key << " = " << value;
	}
	finalIntent = result.intent;

	//判断槽位是否填充
	if (!session.missingSlot.empty()) {
		for (auto it{ result.entities.begin() }; it != result.entities.end();it++) {
			session.missingSlot.erase(it->first);
		}
	}

	//查找意图
	for (auto* intentCtx : l_dsl_ptr->tree->intentDef()) {
		if (intentCtx->ID()->getText() == finalIntent) {
			targetNode = intentCtx;
			break;
		}
	}
	if (!targetNode) {
		//老实说，这个部分不会用到的，毕竟会返回默认意图
		session.lastTimeIntent = "";
		return "我不知道该怎么处理这个意图";
	}
	else {
		LOG_INFO<< "最后确定的意图是：" << finalIntent;
	}
	session.lastTimeIntent = finalIntent;

	//真正进入意图并读取回复
	EcoBotInterpreter interpreter(session.ctx);
	try {
		interpreter.visit(targetNode);
		session.ctx.clear();

	}
	catch (const MissingSlotException&e) {
		session.missingSlot.insert(e.varName);
	}

	//最后返回输出
	return interpreter.getOutput(); 
}