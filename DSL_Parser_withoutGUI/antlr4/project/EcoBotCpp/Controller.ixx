module;
#include "EcoBotParser.h"
#include "EcoBotLexer.h"

export module Controller;
import EcoBotInterpreter;
import IntentRecognition;
import Context;

export void running()
{
	std::ifstream stream("./DSL_script/onlyintent.dsl");
	if (!stream)
		exit(-1);
	
	try {
		antlr4::ANTLRInputStream input(stream);
		EcoBotLexer lexer(&input);
		antlr4::CommonTokenStream tokens(&lexer);
		EcoBotParser parser(&tokens);
		EcoBotParser::ProgramContext* tree{ parser.program() };
		std::cout << "脚本加载完成" << std::endl;

		Context ctx;
		ctx.add("name", "sb");

		EcoBotInterpreter interpreter(ctx);


		std::string userInput;
		while (true) {
			std::cout << "\nYou: ";
			std::getline(std::cin, userInput);
			if (userInput == "exit")
				break;


			std::string targetIntent = llmNLU(userInput);
			//std::cout << "(Debug: 识别意图为 " << targetIntent << ")" << std::endl;

			EcoBotParser::IntentDefContext* targetNode{ nullptr };

			for (auto* intentCtx : tree->intentDef()) {
				if (intentCtx->ID()->getText() == targetIntent) {
					targetNode = intentCtx;
					break;
				}
			}

			if (targetNode) {
				interpreter.visit(targetNode);
			}
			else {
				std::cout << "Robot: 我不知道该怎么处理这个意图 (" << targetIntent << ")" << std::endl;
			}
		}
	}
	catch(const std::exception& e){
		std::cerr << "未知错误：在处理文件 '"  << "' 时发生异常 - " << e.what() << std::endl;
		exit(-1);
	}




}