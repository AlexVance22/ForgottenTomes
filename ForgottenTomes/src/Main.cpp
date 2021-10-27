#include "PCH.h"

#include "CoreMacros.h"
#include "Files/File.h"

#include "Commands/FileManagement.h"
#include "Commands/ElementStorage.h"
#include "Commands/References.h"
#include "Commands/Utilities.h"
#include "Commands/Editing.h"
#include "Commands/Help.h"

#include "Parsing.h"


constexpr uint32_t fnv1a_32(const char* str, size_t count)
{
	return ((count ? fnv1a_32(str, count - 1) : 2166136261u) ^ str[count]) * 16777619u;
}

constexpr uint32_t operator"" _hash(const char* str, size_t count)
{
	return fnv1a_32(str, count);
}


int main()
{
	std::cout << C_RESET;
	system("CLS");
	bool open = false;

	while (true)
	{
		std::vector<Argument> command = getCommand();
		if (command.size() == 0)
			continue;

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