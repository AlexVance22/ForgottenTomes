#include "PCH.h"
#include "Parsing.h"

#include "core/Macros.h"
#include "files/File.h"

#define CMD_ONE_ARG(sname) case sname##_hash: \
	arg.type = Argument::Type::Command; \
	arg.numerical = sname##_hash; \
	break;

#define CMD_TWO_ARG(sname, lname) case sname##_hash: case lname##_hash: \
	arg.type = Argument::Type::Command; \
	arg.numerical = sname##_hash; \
	break;

#define CATEGORY(letter, sname, lname, idx) case letter##_hash: case sname##_hash: case lname##_hash: \
	arg.type = Argument::Type::Category; \
	arg.numerical = idx; \
	break; \

#define GENERAL(name, argtype, num) case name##_hash: \
	arg.type = Argument::Type::argtype; \
	arg.numerical = num; \
	break;


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
		CMD_ONE_ARG("dir")
		CMD_ONE_ARG("cls")
		CMD_TWO_ARG("hlp", "help")
		CMD_TWO_ARG("lst", "list")
		CMD_TWO_ARG("slt", "select")
		CMD_TWO_ARG("vew", "view")
		CMD_TWO_ARG("lkp", "lookup")
		CMD_ONE_ARG("add")
		CMD_ONE_ARG("del")
		CMD_TWO_ARG("edt", "edit")
		CMD_TWO_ARG("rnm", "rename")
		CMD_ONE_ARG("new")
		CMD_TWO_ARG("opn", "open")
		CMD_ONE_ARG("close")
		CMD_TWO_ARG("ext", "exit")

		CATEGORY("s", "ses", "session", 0)
		CATEGORY("l", "loc", "location", 1)
		CATEGORY("c", "cha", "character", 2)
		CATEGORY("i", "itm", "item", 3)

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

		GENERAL("end", Index, -1)
		GENERAL("true", Bool, 1)
		GENERAL("false", Bool, 0)

		case "a"_hash: case "art"_hash: case "article"_hash:
			arg.type = Argument::Type::Special;
			arg.numerical = 0;
			break;

		GENERAL("*", Special, 1)
		GENERAL("none", Special, 2)
		}

		command.push_back(arg);
	}

	return command;
}