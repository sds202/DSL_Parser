#define WIN32_LEAN_AND_MEAN 
#include<Windows.h>
#include <drogon/drogon.h>

import std;
import Controller;

drogon::Task<drogon::HttpResponsePtr> Chat(drogon::HttpRequestPtr req)
{
    auto resp{ drogon::HttpResponse::newHttpResponse() };

    std::string userId = req->getHeader("X-User-ID");
    if (userId.empty()) {
        userId = "visitor";
    }

    std::string userInput(req->getBody());
    std::string result = co_await async_web_running(userId, userInput);
    resp->setBody(result);
    co_return resp;
}

drogon::Task<drogon::HttpResponsePtr> Configure(drogon::HttpRequestPtr req)
{
    auto resp{ drogon::HttpResponse::newHttpResponse() };

    std::string newDslPath = std::string(req->getBody());

    if (newDslPath.empty()) {
        resp->setStatusCode(drogon::k400BadRequest);
        resp->setBody("Error: Wrong path. ");
        co_return resp;
    }

    LOG_INFO << "管理员正在请求切换 DSL 至: " << newDslPath;

    bool success = initOrReloadDSL(newDslPath);

    if (success) {
        resp->setStatusCode(drogon::k200OK);
        resp->setBody("Success: DSL reloaded. System is running on new logic.");
    }
    else {
        resp->setStatusCode(drogon::k500InternalServerError);
        resp->setBody("Failed: Syntax error or file not found. System kept old logic.");
    }

    co_return resp;
}

int main()
{
	SetConsoleOutputCP(65001);
	SetConsoleCP(CP_UTF8);

    drogon::app().setLogLevel(trantor::Logger::kDebug);
    drogon::app().setClientMaxBodySize(5*1024);

    initOrReloadDSL("./DSL_script/test1.dsl");

    drogon::app().registerHandler(
        "/",
        [](drogon::HttpRequestPtr req) -> drogon::Task<drogon::HttpResponsePtr> {
            return Chat(req);
        },
        { drogon::Post }
    );
    drogon::app().registerHandler(
        "/admin",
        [](drogon::HttpRequestPtr req) -> drogon::Task<drogon::HttpResponsePtr> {
            return Configure(req);
        },
        { drogon::Post }
    );

    drogon::app().addListener("0.0.0.0", 8080);

    drogon::app().run();
    return 0;
}