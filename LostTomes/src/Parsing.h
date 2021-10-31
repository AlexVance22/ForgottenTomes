#pragma once

struct Argument
{
	enum class Type { None = -1, Command, Category, Index, Bool, Special };
	Type type = Type::None;
	int64_t numerical = 0;
	std::string str;
};


constexpr uint32_t operator ""_hash(const char* str, size_t count)
{
	uint32_t hash = 2166136261u;

	for (size_t i = 0; i < count; i++)
		hash = (hash ^ str[i]) * 16777619u;

	return hash;
}


bool isInt(const std::string& str);

std::vector<Argument> getCommand();