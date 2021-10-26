#include "PCH.h"

#include "CoreMacros.h"
#include "CMDenums.h"

#include "Commands/FileManagement.h"
#include "Commands/ElementStorage.h"
#include "Commands/References.h"
#include "Commands/Utilities.h"
#include "Commands/Editing.h"


bool isNumber(const std::string& str)
{
	for (char c : str)
	{
		if (!std::isdigit(c))
			return false;
	}
	return true;
}


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
		std::cout << "Add an item to a group, or an article to an item\n\
-To add item to group: add { group type } { index OR 'end' }\n\
-To add article to item: add { group type and index OR '.' character } article { index OR 'end' }\n\
-Valid group types: 'session', location', 'character', 'item'\n\
-Indices must be positive integers no larger than the size of the respective group\n" << std::endl;
		break;
	case CMD::DEL:
		std::cout << "Remove an item from a group, or an article from an item\n\
-To remove item from group: del { group type } { index OR 'end' }\n\
-To remove article from item: del { group type and index OR '.' character } article { index OR 'end' }\n\
-Valid group types: 'session', location', 'character', 'item'\n\
-Indices must be positive integers no larger than the size of the respective group\n" << std::endl; 
		break;
	case CMD::LST:
		std::cout << "List all items in a given group\n\
-To use: list { group type }\n\
-Valid group types: 'session', location', 'character', 'item'\n" << std::endl;
		break;
	case CMD::SLT:
		std::cout << "Bind given item to '.' character shorthand\n\
-To use: select { group type } { index }\n\
-Selected item must already exist\n\
-Valid group types: 'session', location', 'character', 'item'\n\
-Indices must be positive integers no larger than the size of the respective group\n" << std::endl;
		break;
	case CMD::VEW:
		std::cout << "View contents of a given item\n\
-To use: view { group type and index OR '.' character }\n\
-Valid group types: 'session', location', 'character', 'item'\n\
-Indices must be positive integers no larger than the size of the respective group\n" << std::endl;
		break;
	case CMD::LKP:
		std::cout << "Lookup all referenced items in a given article\n\
-To use: lookup { group type and index OR '.' character } article { index }\n\
-Valid group types: 'session', location', 'character', 'item'\n\
-Indices must be positive integers no larger than the size of the respective group\n\n\
-A list of referenced item in the article will be shown and any element can be jumped to by specifying the index\n\
-If the element with the given name does not exist, a 'not implemented' flag will be shown\n\
-Alternatively, type 'exit' to return to main interface\n" << std::endl;
		break;
	case CMD::EDT:
		std::cout << "Edit contents of a given article\n\
-To use: edit { group type and index OR '.' character } article { index }\n\
-Valid group types: 'session', location', 'character', 'item'\n\
-Indices must be positive integers no larger than the size of the respective group\n\n\
-This will open up a notepad window with the article loaded in as a '.txt' file\n\
-While editing, names of other items can be wrapped in '[]' to denote a reference (see 'lookup' command)\n" << std::endl;
		break;
	case CMD::RNM:
		std::cout << "Rename a given item or article\n\
-To rename item: rename { group type } { index }\n\
-To rename article: rename { group type and index OR '.' character } article { index }\n\
-Valid group types: 'session', location', 'character', 'item'\n\
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
		LOG_ERROR("unrecognised command");
		break;
	}
}


std::vector<int> getCommand()
{
	std::string cmd;

	std::cout << ">";
	std::cin.ignore(0);
	std::getline(std::cin, cmd);
	
	std::vector<int> commands;
	for (std::stringstream tokens(cmd); tokens >> cmd;)
	{
		if (isNumber(cmd))
			commands.push_back(std::stoi(cmd));
		else
			commands.push_back(strHash(cmd));
	}

	system("CLS");

	return commands;
}


int main()
{
	std::cout << C_RESET;
	system("CLS");
	bool open = false;

	while (true)
	{
		std::vector<int> command = getCommand();
		if (command.size() == 0)
			continue;

		switch ((CMD)command[0])
		{
		case CMD::CRT: case CMD::OPN: case CMD::HLP:
			break;
		case CMD::EXT:
			return 0;
		default:
			if (!open)
			{
				LOG_ERROR("no file open");
				continue;
			}
		}

		switch ((CMD)command[0])
		{
		case CMD::HLP:
			cmdHelp(command);
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
		case CMD::ADD:
			if (cmdAdd(command))
				cmdSave();
			break;
		case CMD::DEL:
			if (cmdDel(command))
				cmdSave();
			break;
		case CMD::EDT:
			if (cmdEdit(command))
				cmdSave();
			break;
		case CMD::RNM:
			if (cmdRename(command))
				cmdSave();
			break;
		case CMD::CRT:
			if (cmdCreate())
				open = true;
			break;
		case CMD::OPN:
			if (cmdOpen())
				open = true;
			break;
		default:
			LOG_ERROR("unrecognised command");
		}
	}
}