#include "PCH.h"
#include "Parsing.h"

#include "core/Macros.h"
#include "files/File.h"


constexpr uint32_t fnv1a(const char* str, size_t count)
{
	uint32_t hash = 2166136261u;

	for (size_t i = 0; i < count; i++)
		hash = (hash ^ str[i]) * 16777619u;

	return hash;
}


bool isInt(const std::string& str)
{
	if (!std::isdigit(str[0]) && str[0] != '-')
		return false;

	for (size_t i = 1; i < str.size(); i++)
	{
		if (!std::isdigit(str[i]))
			return false;
	}
	return true;
}


std::vector<Argument> getCommand()
{
	std::string cmd;
	std::cout << ">";
	std::cin.ignore(0);
	std::getline(std::cin, cmd);

	std::vector<Argument> command;
	for (std::stringstream tokens(cmd); tokens >> cmd;)
	{
		Argument arg;
		arg.str = cmd;
		uint32_t hash = fnv1a(cmd.c_str(), cmd.size());

		if (isInt(cmd))
		{
			arg.type = Argument::Type::Index;
			arg.numerical = std::stoi(cmd);
			if (arg.numerical < -1)
			{
				LOG_ERROR("invalid index argument");
				return {};
			}
			command.push_back(arg);
			continue;
		}

		switch (hash)
		{
		case "cls"_hash:
			arg.type = Argument::Type::Command;
			arg.numerical = "cls"_hash;
			break;
		case "hlp"_hash: case "help"_hash:
			arg.type = Argument::Type::Command;
			arg.numerical = "hlp"_hash;
			break;
		case "lst"_hash: case "list"_hash:
			arg.type = Argument::Type::Command;
			arg.numerical = "lst"_hash;
			break;
		case "slt"_hash: case "select"_hash:
			arg.type = Argument::Type::Command;
			arg.numerical = "slt"_hash;
			break;
		case "vew"_hash: case "view"_hash:
			arg.type = Argument::Type::Command;
			arg.numerical = "vew"_hash;
			break;
		case "lkp"_hash: case "lookup"_hash:
			arg.type = Argument::Type::Command;
			arg.numerical = "lkp"_hash;
			break;
		case "add"_hash:
			arg.type = Argument::Type::Command;
			arg.numerical = "add"_hash;
			break;
		case "del"_hash:
			arg.type = Argument::Type::Command;
			arg.numerical = "del"_hash;
			break;
		case "edt"_hash: case "edit"_hash:
			arg.type = Argument::Type::Command;
			arg.numerical = "edt"_hash;
			break;
		case "rnm"_hash: case "rename"_hash:
			arg.type = Argument::Type::Command;
			arg.numerical = "rnm"_hash;
			break;
		case "new"_hash:
			arg.type = Argument::Type::Command;
			arg.numerical = "new"_hash;
			break;
		case "opn"_hash: case "open"_hash:
			arg.type = Argument::Type::Command;
			arg.numerical = "opn"_hash;
			break;

		case "s"_hash: case "ses"_hash: case "session"_hash:
			arg.type = Argument::Type::Category;
			arg.numerical = 0;
			break;
		case "l"_hash: case "loc"_hash: case "location"_hash:
			arg.type = Argument::Type::Category;
			arg.numerical = 1;
			break;
		case "c"_hash: case "cha"_hash: case "character"_hash:
			arg.type = Argument::Type::Category;
			arg.numerical = 2;
			break;
		case "i"_hash: case "itm"_hash: case "item"_hash:
			arg.type = Argument::Type::Category;
			arg.numerical = 3;
			break;
		case "."_hash: {
			arg.type = Argument::Type::Category;
			auto sel = File::Selected();
			if (sel)
			{
				arg.numerical = sel.value().category;
				command.push_back(arg);

				arg.type = Argument::Type::Index;
				arg.str = std::to_string(sel.value().element);
				arg.numerical = sel.value().element;
			}
			else
			{
				LOG_ERROR("no item selected");
				return {};
			}
			break; }

		case "end"_hash:
			arg.type = Argument::Type::Index;
			arg.numerical = -1;
			break;

		case "true"_hash:
			arg.type = Argument::Type::Bool;
			arg.numerical = 1;
			break;
		case "false"_hash:
			arg.type = Argument::Type::Bool;
			arg.numerical = 0;
			break;

		case "a"_hash: case "art"_hash: case "article"_hash:
			arg.type = Argument::Type::Special;
			arg.numerical = 0;
			break;
		case "*"_hash:
			arg.type = Argument::Type::Special;
			arg.numerical = 1;
			break;
		}

		command.push_back(arg);
	}

	return command;
}