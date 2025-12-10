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
static DSLResources g_dsl;

struct UserSession {
	Context ctx;
	std::string lastTimeIntent;
	std::set<std::string> missingSlot;
};
static std::map<std::string, UserSession> g_sessions;
static std::mutex g_session_mtx;

export void initDSL(std::string scriptPath)
{
	g_dsl.fileStream = std::make_unique<std::ifstream>(scriptPath);

	if (!g_dsl.fileStream->is_open()) {
		std::cerr << "Fatal Error: Cannot open DSL script: " << scriptPath << std::endl;
		exit(-1);
	}

	g_dsl.input = std::make_unique<antlr4::ANTLRInputStream>(*g_dsl.fileStream);
	g_dsl.lexer = std::make_unique<EcoBotLexer>(g_dsl.input.get());
	g_dsl.tokens = std::make_unique<antlr4::CommonTokenStream>(g_dsl.lexer.get());
	g_dsl.parser = std::make_unique<EcoBotParser>(g_dsl.tokens.get());

	g_dsl.tree = g_dsl.parser->program();
	LOG_INFO << "脚本加载完成";


	for (auto* intent : g_dsl.tree->intentDef()) {
		std::string intentName{ intent->ID()->getText() };
		g_dsl.intents.push_back(intentName);
		for (auto* stmt : intent->stmtList()->stmt()) {
			if (stmt->requireStmt()) {
				auto* reqCtx{ stmt->requireStmt() };
				std::string keyword{ reqCtx->ID()->getText() };
				g_dsl.keywords.push_back(keyword);
			}
			else if (stmt->callStmt()) {
				auto* callCtx{ stmt->callStmt() };
				if (callCtx->ID()) {
					std::string keyword{ callCtx->ID()->getText() };
					g_dsl.keywords.push_back(keyword);
				}
			}
		}
	}

	//// 建议用 Map 结构，这样才能知道哪个意图对应哪些变量
	//std::map<std::string, std::vector<std::string>> intentSchema;

	//for (auto* intent : g_dsl.tree->intentDef()) {
	//	std::string intentName = intent->ID()->getText();

	//	// 临时存当前意图需要的变量名
	//	std::vector<std::string> requiredVars;

	//	for (auto* stmt : intent->stmtList()->stmt()) {
	//		// 【补全部分】检查是否为 require 语句
	//		if (stmt->requireStmt()) {
	//			// 获取 require 语句的上下文
	//			auto* reqCtx = stmt->requireStmt();

	//			// 提取 ID 的文本 (即变量名，如 order_id)
	//			std::string varName = reqCtx->ID()->getText();

	//			requiredVars.push_back(varName);
	//		}
	//	}

	//	// 存入 Schema Map
	//	intentSchema[intentName] = requiredVars;
	//}
}
export std::string web_running(std::string userId,std::string userInput)
{
	EcoBotParser::IntentDefContext* targetNode{ nullptr };
	std::string finalIntent;

	auto [iter, isNew] {g_sessions.try_emplace(userId)};
	
	UserSession& session{ iter->second };

	if (isNew) {
		session.ctx.add("user_id", userId);
	}

	//LLM 识别
	initPrompt(g_dsl.intents, g_dsl.keywords,session.lastTimeIntent,session.missingSlot);
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
	for (auto* intentCtx : g_dsl.tree->intentDef()) {
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
	EcoBotInterpreter interpreter(g_sessions[userId].ctx);
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