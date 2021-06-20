#include "PCH.h"

#include "Files/File.h"
#include "CMDenums.h"

#include "Commands/FileManagement.h"
#include "Commands/ElementStorage.h"
#include "Commands/References.h"
#include "Commands/Utilities.h"
#include "Commands/Editing.h"


void cmdHelp(const std::vector<int>& command)
{
	if (command.size() == 1)
	{
		std::cout << "ALL COMMANDS:\n\n";

		std::cout << "-add\n\
-del\n\
-list\n\
-select\n\
-view\n\
-lookup\n\
-edit\n\
-rename\n\
-new\n\
-open\n" << std::endl;
	}
	else switch ((CMD)command[1])
	{
	case CMD::ADD:
		std::cout << "Add an element to a group, or an article to an element\n\
-To add element to group: add { group type } { index OR 'end' }\n\
-To add article to element: add { group type and index OR '.' character } article { index OR 'end' }\n\
-Valid group types: 'session', location', 'character'\n\
-Indices must be positive integers no larger than the size of the respective group\n" << std::endl;
		break;
	case CMD::DEL:
		std::cout << "Remove an element from a group, or an article from an element\n\
-To remove element from group: del { group type } { index OR 'end' }\n\
-To remove article from element: del { group type and index OR '.' character } article { index OR 'end' }\n\
-Valid group types: 'session', location', 'character'\n\
-Indices must be positive integers no larger than the size of the respective group\n" << std::endl; 
		break;
	case CMD::LST:
		std::cout << "List all elements in a given group\n\
-To use: list { group type }\n\
-Valid group types: 'session', location', 'character'\n" << std::endl;
		break;
	case CMD::SLT:
		std::cout << "Bind given element to '.' character\n\
-To use: select { group type } { index }\n\
-Selected element must already exist\n\
-Valid group types: 'session', location', 'character'\n\
-Indices must be positive integers no larger than the size of the respective group\n" << std::endl;
		break;
	case CMD::VEW:
		std::cout << "View contents of a given element\n\
-To use: view { group type and index OR '.' character }\n\
-Valid group types: 'session', location', 'character'\n\
-Indices must be positive integers no larger than the size of the respective group\n" << std::endl;
		break;
	case CMD::LKP:
		std::cout << "Lookup all referenced elements in a given article\n\
-To use: lookup { group type and index OR '.' character } article { index }\n\
-Valid group types: 'session', location', 'character'\n\
-Indices must be positive integers no larger than the size of the respective group\n\n\
-A list of referenced elements in the article will be shown and any element can be jumped to by specifying the index\n\
-If the element with the given name does not exist, a 'not implemented' flag will be shown\n\
-Alternatively, type 'exit' to return to main interface\n" << std::endl;
		break;
	case CMD::EDT:
		std::cout << "Edit contents of a given article\n\
-To use: edit { group type and index OR '.' character } article { index }\n\
-Valid group types: 'session', location', 'character'\n\
-Indices must be positive integers no larger than the size of the respective group\n\n\
-This will open up a notepad window with the article loaded in as a '.txt' file\n\
-While editing, names of other elements can be wrapped in '[]' to denote a reference (see 'lookup' command)\n" << std::endl;
		break;
	case CMD::RNM:
		std::cout << "Rename a given element or article\n\
-To rename element: rename { group type } { index }\n\
-To rename article: rename { group type and index OR '.' character } article { index }\n\
-Valid group types: 'session', location', 'character'\n\
-Indices must be positive integers no larger than the size of the respective group\n" << std::endl;
		break;
	case CMD::CRT:
		std::cout << "Create a new campaign\n\
-To use: new\n" << std::endl;
		break;
	case CMD::OPN:
		std::cout << "Open an existing campaign\n\
-To use: open\n" << std::endl;
		break;
	default:
		std::cout << "---\nERROR: unrecognised command\n---\n";
		break;
	}
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

	std::cin.ignore(0);
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
	std::vector<std::future<void>> saveProcesses;

	bool open = false;

	while (true)
	{
		std::cout << ">";

		std::vector<int> command = getCommand();

		saveProcesses.clear();

		switch ((CMD)command[0])
		{
		case CMD::CRT: case CMD::OPN: case CMD::HLP:
			break;
		case CMD::EXT:
			return 0;
		default:
			if (File::Get().dir == "")
			{
				std::cout << "---\nERROR: no file open\n---\n";
				goto end;
			}
		}

		switch ((CMD)command[0])
		{
		case CMD::ADD:
			if (cmdAdd(command))
				cmdSave(saveProcesses);
			break;
		case CMD::DEL:
			if (cmdDel(command))
				cmdSave(saveProcesses);
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
		case CMD::LKP:
			cmdLookup(command);
			break;

		case CMD::EDT:
			if (cmdEdit(command))
				cmdSave(saveProcesses);
			break;
		case CMD::RNM:
			if (cmdRename(command))
				cmdSave(saveProcesses);
			break;

		case CMD::HLP:
			cmdHelp(command);
			break;

		case CMD::CRT:
			if (cmdCreate())
				open = true;
			break;
		case CMD::OPN:
			if (cmdOpen())
				open = true;
			break;

		case CMD::INV:
			std::cout << "---\nERROR: empty command\n---\n";
			break;

		default:
			std::cout << "---\nERROR: unrecognised command\n---\n";
		}

	end:;
	}
}