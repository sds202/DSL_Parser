module;
#include"drogon/drogon.h"
#include"json.hpp"

export module IntentRecognition;

export struct NLUResult {
	std::string intent;
	std::map<std::string, std::string> entities;

	NLUResult() : intent("GREET") {}
};
const std::string API_KEY{ "d2856e0dc8a04b6faa2bcaf28c2a979a.EBL2C4nV14ShmO9x" };
const std::string API_HOST{ "https://open.bigmodel.cn" };
const std::string MOCK_API_HOST{ "http://127.0.0.1:8081" };
const std::string API_PATH{ "/api/paas/v4/chat/completions" };
const std::string MODEL{"GLM-4.5-Air"};
const std::string SYS_PROMPT_1{
	R"(你是一个意图识别助手。这是一个多轮对话场景。请分析用户的输入，完成以下任务。

    输入信息包含：
    1. 用户当前输入
    2. 可选的意图列表
    3. 可选的实体类型列表
    4. 上一次对话的意图 (last_intent)
    5. 上一次对话缺失的槽位 (missing_slots)

    ★★★ 最高优先级规则 (Context Logic) ★★★：
    如果 【上一次缺失的实体 (missing_slots)】 不为空，且用户的输入看起来正是在补充该实体的信息：
    1. 你必须 **强制保持** 意图为 【上一次对话的意图 (last_intent)】。
    2. 绝对 **不要** 将其识别为新的意图（即使看起来像）。
    3. 只需提取实体值。

    常规要求：
    1. 如果没有缺失槽位，或者用户输入明显打断了之前的流程（例如“算了，我不退款了，我要查订单”），则根据当前输入识别最匹配的新意图。
    2. 提取实体值。如果实体在输入中未提及，不要包含在结果中。
    3. 严格只返回 JSON 格式，不要包含 Markdown 标记，不要包含任何解释。
	4. 实在没有匹配的意图，就返回看起来像默认的意图（例如“GREET”，前提是该意图必须存在于意图列表中）。

    返回格式示例：
    {
      "intent": "QUERY_ORDER",
      "entities": {
        "order_id": "12345"
      }
    })"
};

export class IntentRecognition
{
private:
	std::string initPrompt(const std::vector<std::string>& intents, const std::vector<std::string>& keywords, std::string_view lastTimeIntent, const std::set<std::string>& missingSlot);
public:
	drogon::Task<NLUResult> llmNLU(std::string_view input, const std::vector<std::string>& intents, const std::vector<std::string>& keywords, std::string_view lastTimeIntent, const std::set<std::string>& missingSlot);
};

//implementations

std::string IntentRecognition::initPrompt(const std::vector<std::string>& intents,const std::vector<std::string>& keywords,std::string_view lastTimeIntent,const std::set<std::string>& missingSlot)
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
	oss << "]";

	return oss.str();
}

export drogon::Task<NLUResult> IntentRecognition::llmNLU(std::string_view input, const std::vector<std::string>& intents, const std::vector<std::string>& keywords, std::string_view lastTimeIntent, const std::set<std::string>& missingSlot)
{
	NLUResult result; //默认是GREET

	std::string system_prompt{initPrompt(intents,keywords,lastTimeIntent,missingSlot)};

	auto client{ drogon::HttpClient::newHttpClient(MOCK_API_HOST)};
	auto req{ drogon::HttpRequest::newHttpRequest() };
	req->setMethod(drogon::Post);
	req->setPath(API_PATH); 
	req->addHeader("Authorization", "Bearer " + std::string(API_KEY));
	req->setContentTypeCode(drogon::CT_APPLICATION_JSON);

	nlohmann::json requestBody = {
		{"model", MODEL}, 
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

	req->setBody(requestBody.dump());

	try {
		auto resp = co_await client->sendRequestCoro(req);

		if (resp->getStatusCode() == 200) {
			auto response = nlohmann::json::parse(resp->getBody());

			if (response.contains("choices") && !response["choices"].empty()) {
				std::string content = response["choices"][0]["message"]["content"];

				// --- 清洗数据：去除可能存在的 Markdown 标记 ---
				size_t jsonStart = content.find("{");
				size_t jsonEnd = content.rfind("}");
				if (jsonStart != std::string::npos && jsonEnd != std::string::npos) {
					content = content.substr(jsonStart, jsonEnd - jsonStart + 1);
				}
				else {
					// 找不到 {}，说明 AI 胡言乱语了
					std::cerr << "[Error] LLM 返回的不是 JSON: " << content << std::endl;
					co_return result;
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

				LOG_INFO << "AI识别出的意图: " << result.intent << ", 提取实体数: " << result.entities.size();
				co_return result;
			}
		}
		else {
			LOG_ERROR << "HTTP Error: " << resp->getStatusCode() << " " << resp->getBody();
		}
	}
	catch (const std::exception& e) {
		LOG_ERROR << "NLU Exception: " << e.what();
	}

	co_return result;
}


//export std::string mockNLU(std::string input)
//{
//	if (input.find("单") != std::string::npos)
//		return "QUERY_ORDER";
//	if (input.find("退") != std::string::npos)
//		return "REFUND";
//	return "GREET";
//}