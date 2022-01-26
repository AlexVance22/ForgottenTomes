#include "PCH.h"
#include "Helpers.h"

#include "core/Macros.h"
#include "core/Exceptions.h"

#include "files/File.h"

#include "Parsing.h"


ItemLocation parseLocStr(const std::vector<Argument>& command, size_t idx)
{
	ItemLocation loc;

	if (command[idx].type != Argument::Type::Category)
		throw InvalidCategory("category argument not found");

	if (command[idx].numerical < 0 || command[idx].numerical > 3)
		throw InvalidArgument("invalid category argument");

	loc.category = (size_t)command[idx++].numerical;

	if (command[idx].type != Argument::Type::Index)
		throw InvalidElement("element index argument not found");

	loc.element = (int)command[idx++].numerical;

	if (idx == command.size())
		return loc;

	if (command[idx].type != Argument::Type::Special || command[idx++].numerical != 0)
		throw InvalidArgument("invalid trailing arguments");

	loc.article = (int)command[idx].numerical;

	return loc;
}

const fs::path categoryPath(size_t cIndex) noexcept
{
	switch (cIndex)
	{
	case 0:
		return File::Get().rootdir / "sessions";
	case 1:
		return File::Get().rootdir / "locations";
	case 2:
		return File::Get().rootdir / "characters";
	case 3:
		return File::Get().rootdir / "items";
	}

	return "";
}

void printFile(const fs::path& filepath)
{
	std::ifstream stream(filepath);
	if (!stream.is_open())
		throw FileNotFound("unable to open file to print");

	for (std::string line; std::getline(stream, line); std::cout << line << '\n');
}