#pragma once

struct Argument
{
	enum class Type { Command, Category, Index, Special };
	Type type;

	std::string str;
	int64_t numerical;
};


constexpr uint32_t fnv1a(const char* str, size_t count)
{
	uint32_t hash = 2166136261u;

	for (size_t i = 0; i < count; i++)
		hash = (hash ^ str[i]) * 16777619u;

	return hash;
}

constexpr uint32_t operator ""_hash(const char* str, size_t count)
{
	return fnv1a(str, count);
}


bool isNumber(const std::string& str);

std::vector<Argument> getCommand();