#define WIN32_LEAN_AND_MEAN 
#include<Windows.h>
#include <drogon/drogon.h>

import std;
import AdminController;
import UserController;
import ChatService;

int main(int argc,char* argv[])
{
	SetConsoleOutputCP(65001);
	SetConsoleCP(CP_UTF8);

    drogon::app().setLogLevel(trantor::Logger::kDebug);
    drogon::app().setClientMaxBodySize(5*1024);

    bool logToFile{ false };
    std::string dslPath;
    std::vector<std::string> args(argv, argv + argc);
    for (const auto& arg : args) {
        if (arg == "--file-log") {
            logToFile = true;
            break;
        }
        else if (arg.find("--dsl-path=") == 0) {
            dslPath = arg.substr(11);  

            if (dslPath.front() == '"' && dslPath.back() == '"') {
                dslPath = dslPath.substr(1, dslPath.length() - 2);
            }
        }
    }

    if (logToFile) {
        drogon::app().setLogPath("./logs", "DSL");
    }


    ChatService::instance().initOrReloadDSL(dslPath);

    drogon::app().registerHandler(
        "/",
        [](drogon::HttpRequestPtr req) -> drogon::Task<drogon::HttpResponsePtr> {
            return UserController::Chat(req);
        },
        { drogon::Post }
    );
    drogon::app().registerHandler(
        "/admin",
        [](drogon::HttpRequestPtr req) -> drogon::Task<drogon::HttpResponsePtr> {
            return AdminController::Configure(req);
        },
        { drogon::Post }
    );

    drogon::app().addListener("0.0.0.0", 8080);

    drogon::app().run();
    return 0;
}