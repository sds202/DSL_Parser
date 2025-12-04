export module Context;
import std;

export class Context
{
private:
	std::unordered_map<std::string, std::string>memory;
public:
	void add(std::string key, std::string value);
	bool contains(std::string key);
	std::string find(std::string key);

};

void Context::add(std::string key, std::string value)
{
	memory.insert_or_assign(std::move(key), std::move(value));
}

bool Context::contains(std::string key)
{
	return memory.contains(key);
}
std::string Context::find(std::string key)
{
	return memory.find(key)->second;
}
