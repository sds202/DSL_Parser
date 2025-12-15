module;
#include <drogon/drogon.h>

export module UserController;
import ChatService;

export class UserController
{
private:
public:
    static drogon::Task<drogon::HttpResponsePtr> Chat(drogon::HttpRequestPtr req);
};

//implementations

drogon::Task<drogon::HttpResponsePtr> UserController::Chat(drogon::HttpRequestPtr req)
{
    auto resp{ drogon::HttpResponse::newHttpResponse() };

    std::string userId = req->getHeader("X-User-ID");
    if (userId.empty()) {
        userId = "visitor";
    }

    std::string userInput(req->getBody());
    std::string result = co_await ChatService::instance().handleInput(userId, userInput);
    resp->setBody(result);
    co_return resp;
}
