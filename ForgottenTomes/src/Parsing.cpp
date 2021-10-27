#include "PCH.h"
#include "Parsing.h"

#include "CoreMacros.h"
#include "Files/File.h"


bool isNumber(const std::string& str)
{
	for (char c : str)
	{
		if (!std::isdigit(c))
			return false;
	}
	return true;
}


constexpr uint32_t fnv1a_32(const char* str, size_t count)
{
	return ((count ? fnv1a_32(str, count - 1) : 2166136261u) ^ str[count]) * 16777619u;
}

constexpr uint32_t operator"" _hash(const char* str, size_t count)
{
	return fnv1a_32(str, count);
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
		uint32_t hash = fnv1a_32(cmd.c_str(), cmd.size());

		if (isNumber(cmd))
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

	system("CLS");

	return command;
}