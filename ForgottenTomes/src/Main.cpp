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
}


int main()
{
	std::cout << C_RESET;
	system("CLS");
	bool open = false;
	bool cls = true;

	while (true)
	{
		std::vector<Argument> command = getCommand();
		if (command.size() == 0)
			continue;

		if (cls)
			system("CLS");

		switch (command[0].numerical)
		{
		case "new"_hash: case "opn"_hash: case "hlp"_hash:
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
		default:
			LOG_ERROR("unrecognised command");
		}
	}
}