module;
#include "EcoBotParser.h"
#include "EcoBotLexer.h"

export module something;
import EcoBotInterpreter;

std::string mockNLU(std::string input)
{
	if (input.find("单") != std::string::npos)
		return "QUERY_ORDER";
	if (input.find("退") != std::string::npos)
		return "REFUND";
	return "GREET";
}

export void Maybe()
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

		EcoBotInterpreter interpreter;


		std::string userInput;
		while (true) {
			std::cout << "\nYou: ";
			std::getline(std::cin, userInput);
			if (userInput == "exit")
				break;

			std::string targetIntent = mockNLU(userInput);
			std::cout << "(Debug: 识别意图为 " << targetIntent << ")" << std::endl;

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