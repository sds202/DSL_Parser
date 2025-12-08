#define WIN32_LEAN_AND_MEAN 
#include<Windows.h>
#include <drogon/drogon.h>

import std;
import Controller;

using namespace drogon;

int main()
{
	SetConsoleOutputCP(65001);
	SetConsoleCP(CP_UTF8);
	//running();

    app().registerHandler("/", [](const HttpRequestPtr& req,
        std::function<void(const HttpResponsePtr&)>&& callback) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setBody("Hello, Drogon on Windows!");
            callback(resp);
        });

    app().addListener("0.0.0.0", 8080);

    app().run();
    return 0;
}