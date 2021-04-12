#include "PCH.h"

#include "File.h"
#include "CMDenums.h"

#include "FileManagement.h"
#include "ElementStorage.h"
#include "Utilities.h"
#include "Editing.h"


void cmdHelp()
{
	std::cout << "ALL COMMANDS:\n\n";

	std::cout << "-add\nAdd item to a group\nSyntax: group {session, location, character} placement {back, index} index {positive integer within group size bounds}\n\n";

	std::cout << "-del\nRemove item from group\nSyntax: group {session, location, character} placement {back, index} index {positive integer within group size bounds}\n\n";

	std::cout << "-list\nList all items in group\nSyntax: group {session, location, character}\n\n";

	std::cout << "-select\nBind item to '-s' keyword\nSyntax: group {session, location, character} index {positive integer within group size bounds}\n\n";

	std::cout << "-view\nView contents of item\nSyntax: group {session, location, character} index {positive integer within group size bounds} OR {'-s' keyword}\n\n";

	std::cout << "-edit\nEdit contents of item\nSyntax: group {session, location, character} index {positive integer within group size bounds} OR {'-s' keyword} element {name, content}\n" << std::endl;
}


std::vector<int> getCommand()
{
	auto isNumber = [](const std::string& str) {
		for (char c : str)
		{
			if (std::isdigit(c) == 0)
				return false;
		}
		return true;
	};

	std::string cmd;
	std::vector<int> commands;

	std::cin.ignore(0, -1);
	std::getline(std::cin, cmd);
	
	for (std::stringstream tokens(cmd); tokens >> cmd;)
	{
		if (isNumber(cmd))
			commands.push_back(std::stoi(cmd));
		else
			commands.push_back(strHash(cmd));
	}

	if (commands.size() == 0)
		commands.push_back(0);

	system("CLS");

	return commands;
}


int main()
{
	while (true)
	{
		std::cout << ">";

		std::vector<int> command = getCommand();

		switch ((CMD)command[0])
		{
		case CMD::ADD:
			if (cmdAdd(command))
				cmdSave();
			break;
		case CMD::DEL:
			if (cmdDel(command))
				cmdSave();
			break;

		case CMD::LST:
			cmdList(command);
			break;
		case CMD::SLT:
			cmdSelect(command);
			break;
		case CMD::VEW:
			cmdView(command);
			break;

		case CMD::EDT:
			if (cmdEdit(command))
				cmdSave();
			break;
		case CMD::RNM:
			if (cmdRename(command))
				cmdSave();
			break;

		case CMD::HLP:
			cmdHelp();
			break;

		case CMD::OPN:
			cmdOpen();
			break;
		case CMD::SVE:
			cmdSave();
			break;
		case CMD::CRT:
			cmdCreate();
			break;

		case CMD::INV:
			std::cout << "---\nERROR: empty command\n---\n";
			break;

		default:
			std::cout << "---\nERROR: unrecognised command\n---\n";
		}
	}
}