module;
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include"httplib.h"
#include"json.hpp"

export module IntentRecognition;
import std;

const std::string API_KEY{ "5280be8dae0f45afb0c9f8fd53ba7c2d.JchavmZVZYL0rMhE" };
const std::string API_HOST{ "open.bigmodel.cn" };
const std::string API_PATH{ "/api/paas/v4/chat/completions" };
const std::string SYSTEM_PROMPT{
	R"(你是一个意图识别助手。请分析用户的输入，并将其归类为以下意图之一：
	- QUERY_ORDER(查询订单 / 物流)
	- REFUND(退款 / 售后)
	- GREET(打招呼 / 其他)

	规则：
	1. 只返回意图代码（例如只返回 "QUERY_ORDER"）。
	2. 不要返回任何解释、标点符号或其他文字。
	3. 如果无法识别，返回 "GREET"。
	)"
};

export std::string llmNLU(std::string_view input)
{
	httplib::SSLClient cli(API_HOST);

	cli.set_read_timeout(30, 0);
	cli.set_bearer_token_auth(API_KEY);

	nlohmann::json requestBody = {
		{"model", "glm-4.5"}, 
		{"messages", {
			{
				{"role", "system"},
				{"content", SYSTEM_PROMPT} 
			},
			{
				{"role", "user"},
				{"content", input}     
			}
		}},
		{"thinking",{
			{"type","disabled"}
		}},
		{"temperature", 0.1}, 
		{"stream", false}     
	};

	auto res{ cli.Post(API_PATH,requestBody.dump(),"application/json") };

	if (res && res->status == 200) {
		try {
			auto response = nlohmann::json::parse(res->body);

			// 提取结果: choices[0].message.content
			if (response.contains("choices") && !response["choices"].empty()) {
				std::string content = response["choices"][0]["message"]["content"];

				// 简单的字符串清理 (去空格/换行)
				content.erase(0, content.find_first_not_of(" \t\n\r\""));
				content.erase(content.find_last_not_of(" \t\n\r\"") + 1);

				std::cout << "[Debug] LLM 识别结果: [" << content << "]" << std::endl;
				return content;
			}
		}
		catch (const std::exception& e) {
			std::cerr << "JSON 解析失败: " << e.what() << std::endl;
		}
	}
	else {
		std::cerr << "请求失败 Status: " << (res ? res->status : -1) << std::endl;
		if (res) std::cerr << "Error Body: " << res->body << std::endl;
	}
	return "GREET";
}

export std::string mockNLU(std::string input)
{
	if (input.find("单") != std::string::npos)
		return "QUERY_ORDER";
	if (input.find("退") != std::string::npos)
		return "REFUND";
	return "GREET";
}