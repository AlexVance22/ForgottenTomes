#include "PCH.h"
#include "Help.h"

#include "CoreMacros.h"

#include "Parsing.h"


constexpr uint32_t fnv1a_32(const char* str, size_t count)
{
	return ((count ? fnv1a_32(str, count - 1) : 2166136261u) ^ str[count]) * 16777619u;
}

constexpr uint32_t operator"" _hash(const char* str, size_t count)
{
	return fnv1a_32(str, count);
}


void cmdHelp(const std::vector<Argument>& command)
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
	else switch (command[1].numerical)
	{
	case "add"_hash:
		std::cout << "Add an item to a group, or an article to an item\n\
		-To add item to group: add { group type } { index OR 'end' }\n\
		-To add article to item: add { group type and index OR '.' character } article { index OR 'end' }\n\
		-Valid group types: 'session', location', 'character', 'item'\n\
		-Indices must be positive integers no larger than the size of the respective group\n" << std::endl;
		break;
	case "del"_hash:
		std::cout << "Remove an item from a group, or an article from an item\n\
		-To remove item from group: del { group type } { index OR 'end' }\n\
		-To remove article from item: del { group type and index OR '.' character } article { index OR 'end' }\n\
		-Valid group types: 'session', location', 'character', 'item'\n\
		-Indices must be positive integers no larger than the size of the respective group\n" << std::endl;
		break;
	case "lst"_hash:
		std::cout << "List all items in a given group\n\
		-To use: list { group type }\n\
		-Valid group types: 'session', location', 'character', 'item'\n" << std::endl;
		break;
	case "slt"_hash:
		std::cout << "Bind given item to '.' character shorthand\n\
		-To use: select { group type } { index }\n\
		-Selected item must already exist\n\
		-Valid group types: 'session', location', 'character', 'item'\n\
		-Indices must be positive integers no larger than the size of the respective group\n" << std::endl;
		break;
	case "vew"_hash:
		std::cout << "View contents of a given item\n\
		-To use: view { group type and index OR '.' character }\n\
		-Valid group types: 'session', location', 'character', 'item'\n\
		-Indices must be positive integers no larger than the size of the respective group\n" << std::endl;
		break;
	case "lkp"_hash:
		std::cout << "Lookup all referenced items in a given article\n\
		-To use: lookup { group type and index OR '.' character } article { index }\n\
		-Valid group types: 'session', location', 'character', 'item'\n\
		-Indices must be positive integers no larger than the size of the respective group\n\n\
		-A list of referenced item in the article will be shown and any element can be jumped to by specifying the index\n\
		-If the element with the given name does not exist, a 'not implemented' flag will be shown\n\
		-Alternatively, type 'exit' to return to main interface\n" << std::endl;
		break;
	case "edt"_hash:
		std::cout << "Edit contents of a given article\n\
		-To use: edit { group type and index OR '.' character } article { index }\n\
		-Valid group types: 'session', location', 'character', 'item'\n\
		-Indices must be positive integers no larger than the size of the respective group\n\n\
		-This will open up a notepad window with the article loaded in as a '.txt' file\n\
		-While editing, names of other items can be wrapped in '[]' to denote a reference (see 'lookup' command)\n" << std::endl;
		break;
	case "rnm"_hash:
		std::cout << "Rename a given item or article\n\
		-To rename item: rename { group type } { index }\n\
		-To rename article: rename { group type and index OR '.' character } article { index }\n\
		-Valid group types: 'session', location', 'character', 'item'\n\
		-Indices must be positive integers no larger than the size of the respective group\n" << std::endl;
		break;
	case "new"_hash:
		std::cout << "Create a new campaign\n\
		-To use: new\n" << std::endl;
		break;
	case "opn"_hash:
		std::cout << "Open an existing campaign\n\
		-To use: open\n" << std::endl;
		break;
	default:
		LOG_ERROR("unrecognised command");
		break;
	}
}