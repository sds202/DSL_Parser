module;
#include <drogon/drogon.h>

export module AdminController;
import ChatService;

export class AdminController {
public:
    static drogon::Task<drogon::HttpResponsePtr> Configure(drogon::HttpRequestPtr req);
};

//implemetations

drogon::Task<drogon::HttpResponsePtr> AdminController::Configure(drogon::HttpRequestPtr req)
{
    auto resp{ drogon::HttpResponse::newHttpResponse() };

    std::string newDslPath = std::string(req->getBody());

    if (newDslPath.empty()) {
        resp->setStatusCode(drogon::k400BadRequest);
        resp->setBody("Error: Wrong path. ");
        co_return resp;
    }

    LOG_INFO << "管理员正在请求切换 DSL 至: " << newDslPath;

    bool success{ ChatService::instance().initOrReloadDSL(newDslPath) };

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