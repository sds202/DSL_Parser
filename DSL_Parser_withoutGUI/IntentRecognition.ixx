module;
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include"httplib.h"
#include"json.hpp"
#include "trantor/utils/Logger.h"

export module IntentRecognition;

export struct NLUResult {
	std::string intent;
	std::map<std::string, std::string> entities;

	NLUResult() : intent("GREET") {}
};
const std::string API_KEY{ "5280be8dae0f45afb0c9f8fd53ba7c2d.JchavmZVZYL0rMhE" };
const std::string API_HOST{ "open.bigmodel.cn" };
const std::string API_PATH{ "/api/paas/v4/chat/completions" };
const std::string SYS_PROMPT_1{
	R"(你是一个意图识别助手。请分析用户的输入，并结合上次的意图，完成两个任务：
	1.从中提取意图，并将其归类为最后给出的意图之一
	2.从中提取实体，并将其归类为最后给出的实体之一。比如用户输入“我要查订单，订单号1102”，则1102就是一个order_id(如果存在这个实体的话)实体。

	要求：
	1. 分析用户输入，匹配最合适的意图，找不到适当的意图，请返回你觉得是默认的意图，比如打招呼。
	2. 提取实体值。如果实体在输入中未提及，不要包含在结果中。
	3. 严格只返回 JSON 格式，不要包含 Markdown 标记（如 ```json），不要包含任何解释。
	4. 提供了用户上一次的意图和上次缺失的实体输入。
	5. 如果你发现用户的上一次意图不在给出的意图列表中，这可能是由于服务端恰好更换了新的dsl语言导致的，这时请你返回默认的意图。

	返回格式示例：
	{
	  "intent": "QUERY_ORDER",
	  "entities": {
		"order_id": "12345",
		"reason": "不想要了"
	  }
	})"
};

static std::string system_prompt;

export void initPrompt(const std::vector<std::string>& intents,const std::vector<std::string>& keywords,std::string_view lastTimeIntent,const std::set<std::string>& missingSlot)
{
	std::stringstream oss;

	oss << SYS_PROMPT_1;

	oss << "\n意图：[";
	for (std::string_view intent : intents) {
		oss << intent << ' ';
	}
	oss << ']';

	oss << "\n实体：[";
	for (std::string_view keyword : keywords) {
		oss << keyword << ' ';
	}
	oss << ']';

	oss << "\n用户上一次的意图是：" << lastTimeIntent;
	oss << "\n用户上一次缺失的实体输入：[";
	for (std::string_view slot : missingSlot) {//todo
		oss << slot << ' ';
	}

	system_prompt = oss.str();
}

export NLUResult llmNLU(std::string_view input)
{
	httplib::SSLClient cli(API_HOST);

	cli.set_read_timeout(30, 0);
	cli.set_bearer_token_auth(API_KEY);

	nlohmann::json requestBody = {
		{"model", "glm-4.5"}, 
		{"messages", {
			{
				{"role", "system"},
				{"content", system_prompt}
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

	auto res = cli.Post(API_PATH, requestBody.dump(), "application/json");

	NLUResult result; // 默认是 GREET

	if (res && res->status == 200) {
		try {
			auto response = nlohmann::json::parse(res->body);

			if (response.contains("choices") && !response["choices"].empty()) {
				std::string content = response["choices"][0]["message"]["content"];

				// --- 清洗数据：去除可能存在的 Markdown 标记 ---
				// 有些模型喜欢返回 ```json ... ```
				size_t jsonStart = content.find("{");
				size_t jsonEnd = content.rfind("}");
				if (jsonStart != std::string::npos && jsonEnd != std::string::npos) {
					content = content.substr(jsonStart, jsonEnd - jsonStart + 1);
				}
				else {
					// 找不到 {}，说明 AI 胡言乱语了
					std::cerr << "[Error] LLM 返回的不是 JSON: " << content << std::endl;
					return result;
				}

				// --- 解析内部 JSON ---
				auto jsonContent = nlohmann::json::parse(content);

				// 1. 提取意图
				if (jsonContent.contains("intent") && jsonContent["intent"].is_string()) {
					result.intent = jsonContent["intent"];
				}

				// 2. 提取实体
				if (jsonContent.contains("entities") && jsonContent["entities"].is_object()) {
					for (auto& [key, val] : jsonContent["entities"].items()) {
						// 确保值是字符串 (虽然 JSON 值可能是数字，转一下比较安全)
						if (val.is_string()) {
							result.entities[key] = val;
						}
						else {
							result.entities[key] = val.dump(); // 强转为 string
						}
					}
				}

				LOG_INFO << "AI识别出的意图: " << result.intent << ", 提取实体数: " << result.entities.size() ;
				return result;
			}
		}
		catch (const std::exception& e) {
			std::cerr << "[NLU Error] JSON 解析异常: " << e.what() << std::endl;
			std::cerr << "原始响应: " << res->body << std::endl;
		}
	}
	else {
		std::cerr << "[NLU Error] HTTP 请求失败 Status: " << (res ? res->status : -1) << std::endl;
	}

	return result; // 返回默认值 (GREET)
}



export std::string mockNLU(std::string input)
{
	if (input.find("单") != std::string::npos)
		return "QUERY_ORDER";
	if (input.find("退") != std::string::npos)
		return "REFUND";
	return "GREET";
}