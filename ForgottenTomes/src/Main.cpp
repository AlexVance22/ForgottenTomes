#include "PCH.h"

#include "core/Macros.h"
#include "files/File.h"

#include "commands/FileManagement.h"
#include "commands/ElementStorage.h"
#include "commands/References.h"
#include "commands/Utilities.h"
#include "commands/Editing.h"
#include "commands/Help.h"

#include "Parsing.h"


//bug: system function ignoring if condition
void cmdClear(const std::vector<Argument>& command, bool& cls)
{
	if (command.size() == 1)
	{
		system("CLS");
		return;
	}

	if (command[1].type != Argument::Type::Bool && command[1].type != Argument::Type::Index)
	{
		LOG_ERROR("invalid boolean value");
		return;
	}

	cls = (bool)command[1].numerical;
	if (cls)
		system("CLS");

	std::ifstream istream("res/startup.json");
	if (istream.is_open())
	{
		nlohmann::json j;
		istream >> j;
		istream.close();
		j["clearscreen"] = cls;

		std::ofstream ostream("res/startup.json", std::ios::trunc);
		if (ostream.is_open())
		{
			ostream << j;
			ostream.close();
		}
	}
}


bool startup(bool& cls)
{
	std::ifstream stream("res/startup.json");
	if (stream.is_open())
	{
		nlohmann::json j;
		stream >> j;
		stream.close();

		cls = j["clearscreen"];

		auto& sel = File::Get().selected;
		if (!j["selected"].is_null())
		{
			sel.category = j["selected"]["category"];
			sel.element = j["selected"]["element"];
		}

		if (j["lastfile"] == "empty")
			return false;

		if (!File::Get().load(j["lastfile"]))
		{
			LOG_ERROR("failed to reopen last workspace");
			return false;
		}

		std::cout << "Reopened last workspace\n";
		return true;
	}
	LOG_ERROR("startup file missing");
	return false;
}


int main()
{
	std::cout << C_RESET;
	system("CLS");
	bool cls = true;
	bool open = startup(cls);

	while (true)
	{
		std::vector<Argument> command = getCommand();
		if (command.size() == 0)
			continue;

		if (cls)
			system("CLS");

		switch (command[0].numerical)
		{
		case "new"_hash: case "opn"_hash: case "hlp"_hash: case "cls"_hash:
			break;
		case "ext"_hash:
			return 0;
		default:
			if (!open)
			{
				LOG_ERROR("no file open");
				continue;
			}
		}

		switch (command[0].numerical)
		{
		case "dir"_hash:
			std::cout << File::Get().rootdir << '\n';
			break;
		case "cls"_hash:
			cmdClear(command, cls);
			break;
		case "hlp"_hash:
			cmdHelp(command);
			break;
		case "lst"_hash:
			cmdList(command);
			break;
		case "slt"_hash:
			cmdSelect(command);
			break;
		case "vew"_hash:
			cmdView(command);
			break;
		case "lkp"_hash:
			cmdLookup(command);
			break;
		case "add"_hash:
			if (cmdAdd(command))
				cmdSave();
			break;
		case "del"_hash:
			if (cmdDel(command))
				cmdSave();
			break;
		case "edt"_hash:
			if (cmdEdit(command))
				cmdSave();
			break;
		case "rnm"_hash:
			if (cmdRename(command))
				cmdSave();
			break;
		case "new"_hash:
			if (cmdCreate())
				open = true;
			break;
		case "opn"_hash:
			if (cmdOpen())
				open = true;
			break;
		case "close"_hash:
			cmdClose();
			open = false;
			break;
		default:
			LOG_ERROR("unrecognised command");
		}
	}
}