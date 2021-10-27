#include "PCH.h"
#include "Helpers.h"

#include "CoreMacros.h"
#include "Files/File.h"

#include "Parsing.h"


bool parseLocStr(ItemLocation& loc, const std::vector<Argument>& command, size_t idx)
{
	if (command[idx].type != Argument::Type::Category)
	{
		LOG_ERROR("category argument not found");
		return false;
	}
	loc.category = (size_t)command[idx++].numerical;

	if (command[idx].type != Argument::Type::Index)
	{
		LOG_ERROR("index argument not found");
		return false;
	}
	loc.element = (int)command[idx++].numerical;

	if (idx == command.size())
		return true;

	if (command[idx].type != Argument::Type::Special || command[idx++].numerical != 0)
	{
		LOG_ERROR("invalid trailing arguments");
		return false;
	}
	loc.article = (int)command[idx].numerical;

	return true;
}

std::string categoryPath(size_t cIndex)
{
	switch (cIndex)
	{
	case 0:
		return File::Get().rootdir + "/sessions/";
	case 1:
		return File::Get().rootdir + "/locations/";
	case 2:
		return File::Get().rootdir + "/characters/";
	case 3:
		return File::Get().rootdir + "/items/";
	}

	return "";
}

void printFile(const std::string& filepath)
{
	std::ifstream stream(filepath);
	if (stream.is_open())
		for (std::string line; std::getline(stream, line); std::cout << line << '\n');
}