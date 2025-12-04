export module IntentRecognition;
import std;

export std::string mockNLU(std::string input)
{
	if (input.find("单") != std::string::npos)
		return "QUERY_ORDER";
	if (input.find("退") != std::string::npos)
		return "REFUND";
	return "GREET";
}