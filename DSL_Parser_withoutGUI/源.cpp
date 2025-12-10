#define WIN32_LEAN_AND_MEAN 
#include<Windows.h>
#include <drogon/drogon.h>

import std;
import Controller;

drogon::Task<drogon::HttpResponsePtr> hello(drogon::HttpRequestPtr req)
{
    auto resp{ drogon::HttpResponse::newHttpResponse() };
    std::string user_input(req->getBody());
    std::string result = web_running("250", user_input);
    resp->setBody(result);
    co_return resp;
}

int main()
{
	SetConsoleOutputCP(65001);
	SetConsoleCP(CP_UTF8);

    initDSL("./DSL_script/onlyintent.dsl");

    drogon::app().registerHandler(
        "/",
        [](drogon::HttpRequestPtr req) -> drogon::Task<drogon::HttpResponsePtr> {
            return hello(req);
        },
        { drogon::Post }
    );

    drogon::app().addListener("0.0.0.0", 8080);

    drogon::app().run();
    return 0;
}