export module Context;
import std;

export class Context
{
private:
	std::unordered_map<std::string, std::string>memory;
public:
	void add(std::string key, std::string value);
	bool contains(std::string key);
	std::optional<std::string> find(std::string key);
	void clear();

};

void Context::add(std::string key, std::string value)
{
	memory.insert_or_assign(std::move(key), std::move(value));
}
bool Context::contains(std::string key)
{
	return memory.contains(key);
}
std::optional<std::string> Context::find(std::string key)
{
	auto it{ memory.find(key) };
	if (it != memory.end()) {
		return it->second;
	}
	return std::nullopt;
}
void Context::clear()
{
	for (auto it = memory.begin(); it != memory.end(); ) {
		if (it->first != "user_id") {
			it = memory.erase(it);
		}
		else {
			++it;
		}
	}

}
