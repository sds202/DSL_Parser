module;
#include "antlr4/project/EcoBotCpp/EcoBotParser.h"
#include "antlr4/project/EcoBotCpp/EcoBotLexer.h"
#include "drogon/drogon.h"

export module DSLManager;
import std;
import ValidateVisitor;

export struct DSLResources {
	std::unique_ptr<std::ifstream> fileStream;
	std::unique_ptr<antlr4::ANTLRInputStream> input;
	std::unique_ptr<EcoBotLexer> lexer;
	std::unique_ptr<antlr4::CommonTokenStream> tokens;
	std::unique_ptr<EcoBotParser> parser;
	EcoBotParser::ProgramContext* tree = nullptr;

	std::vector<std::string> intents;
	std::vector<std::string> keywords;
};

export class DSLManager
{
private:
	std::expected<std::shared_ptr<DSLResources>, std::string> loadDSLInternal(const std::string& scriptPath);
	std::atomic<std::shared_ptr<DSLResources>> dsl_ptr;
public:
	std::expected<void, std::string> initOrReloadDSL(const std::string& scriptPath);
	std::shared_ptr<DSLResources> loadDSLPtr();
};

class DSLErrorListener :public antlr4::BaseErrorListener {
public:
	std::stringstream errorMsgStream;
	void syntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol, size_t line, size_t charPositionInLine, const std::string& msg, std::exception_ptr e) override {
		errorMsgStream << "[Syntax Error] Line " << line << ":" << charPositionInLine
			<< " - " << msg << "\n";
	}

	std::string getErrorMessage() const {
		return errorMsgStream.str();
	}
};

//implementations

std::expected<std::shared_ptr<DSLResources>,std::string> DSLManager::loadDSLInternal(const std::string& scriptPath)
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

	DSLErrorListener errorListener;

	data->lexer->removeErrorListeners();
	data->parser->removeErrorListeners();

	data->lexer->addErrorListener(&errorListener);
	data->parser->addErrorListener(&errorListener);

	data->tree = data->parser->program();

	//检查语法错误
	if (data->parser->getNumberOfSyntaxErrors() > 0) {
		LOG_ERROR << "Fatal Error: Syntax errors found in DSL script: " << scriptPath;
		std::string allErrors{ errorListener.getErrorMessage() };
		return std::unexpected(allErrors);
	}

	// 检查dsl中的类，方法和参数是否正确
	ValidatorVisitor validator;
	try {
		validator.visit(data->tree);
		LOG_INFO << "脚本无语法错误，通过静态测试。";
	}
	catch (const std::exception& e) {
		LOG_ERROR << "脚本存在错误： " << e.what();
		std::string allErrors{ errorListener.getErrorMessage() + e.what() };
		return std::unexpected(allErrors);
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
std::expected<void,std::string> DSLManager::initOrReloadDSL(const std::string& scriptPath)
{
	auto newDSL = loadDSLInternal(scriptPath);
	
	if (newDSL.has_value()) {
		dsl_ptr.store(newDSL.value());
		LOG_INFO << "脚本初始化/更换完成";
		return {};
	}
	else {
		LOG_ERROR << "脚本加载失败，保持原样";
		return std::unexpected(newDSL.error());
	}
}
std::shared_ptr<DSLResources> DSLManager::loadDSLPtr()
{
	return dsl_ptr.load();
}
