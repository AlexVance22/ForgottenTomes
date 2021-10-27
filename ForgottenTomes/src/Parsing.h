#pragma once

struct Argument
{
	enum class Type { Command, Category, Index, Special };
	Type type;

	std::string str;
	int64_t numerical;
};


bool isNumber(const std::string& str);

std::vector<Argument> getCommand();