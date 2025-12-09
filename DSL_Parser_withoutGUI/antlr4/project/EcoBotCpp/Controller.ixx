module;
#include "EcoBotParser.h"
#include "EcoBotLexer.h"

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
};
static DSLResources g_dsl;

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
	std::cout << "脚本加载完成" << std::endl;
}

export std::string web_running(std::string userInput)
{
	Context ctx;
	ctx.add("name", "sb");
	EcoBotInterpreter interpreter(ctx);

	std::string targetIntent = llmNLU(userInput);
	std::cout << "(Debug: 识别意图为 " << targetIntent << ")" << std::endl;

	EcoBotParser::IntentDefContext* targetNode{ nullptr };

	for (auto* intentCtx : g_dsl.tree->intentDef()) {
		if (intentCtx->ID()->getText() == targetIntent) {
			targetNode = intentCtx;
			break;
		}
	}

	if (targetNode) {
		interpreter.visit(targetNode);
		return interpreter.getOutput();
	}
	else {
		return "我不知道该怎么处理这个意图";
	}
}