#include <drogon/drogon.h>

import std;

const std::string SERVER_URL = "http://127.0.0.1:8080";

int main()
{
	std::thread networkThread([]() {
		drogon::app().setLogLevel(trantor::Logger::kError);
		drogon::app().run();
		});
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	auto client{ drogon::HttpClient::newHttpClient(SERVER_URL) };

	std::cout << "===========================================" << std::endl;
	std::cout << "           EcoBot Admin Console            " << std::endl;
	std::cout << "===========================================" << std::endl;

	std::string line;
	while (true) {
		std::cout << "\n[请输入 DSL 文件路径] > ";
		std::getline(std::cin, line);

		line.erase(0, line.find_first_not_of(" \t\r\n"));
		line.erase(line.find_last_not_of(" \t\r\n") + 1);

		std::promise<void> reqDone;
		auto future{ reqDone.get_future() };

		auto req{ drogon::HttpRequest::newHttpRequest() };
		req->setMethod(drogon::Post);
		req->setPath("/admin");
		req->setBody(line);
		std::cout << "正在发送请求..." << std::endl;

		client->sendRequest(req, [&](drogon::ReqResult result, const drogon::HttpResponsePtr& response) {
			if (result == drogon::ReqResult::Ok) {
				if (response->getStatusCode() == drogon::k200OK) {
					std::cout << "[成功] " << response->getBody() << std::endl;
				}
				else {
					std::cout << "[失败] 状态码: " << response->getStatusCode() << "\n信息: "<< response->getBody()  << std::endl;
				}
			}
			else {
				std::cout << "[网络错误] 无法连接服务器。" << std::endl;
			}

			reqDone.set_value();
			});

		future.wait();
	}
}