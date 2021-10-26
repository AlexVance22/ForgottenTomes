#include "PCH.h"
#include "Utilities.h"

#include "CoreMacros.h"

#include "Files/File.h"
#include "CMDenums.h"
#include "Helpers.h"


void viewElement(size_t cIndex, int eIndex)
{
	const Element& e = File::Category(cIndex)[eIndex];

	std::cout << "Name: " << e.name << '\n';

	for (size_t i = 0; i < e.content.size(); i++)
	{
		std::cout << "\n-----------------------\n";

		std::cout << i << " - " << e.content[i] << ":" << "\n\n";
		std::string path = File::Get().rootdir;
		appendCategory(path, cIndex);

		printFile(path + e.name + '/' + e.content[i] + ".txt");
	}
}

void viewArticle(size_t cIndex, int eIndex, int aIndex)
{
	const Element& e = File::Category(cIndex)[eIndex];

	std::cout << e.name + " article " << aIndex << ":\n\n";
	std::cout << e.content[aIndex] + "\n\n";

	std::string path = File::Get().rootdir;
	appendCategory(path, cIndex);

	printFile(path + e.name + '/' + e.content[aIndex] + ".txt");
}


bool cmdList(const std::vector<int>& command)
{
	std::cout << C_CYAN;

	if (!listElements((ARG)command[1]))
	{
		LOG_ERROR("invalid element type");
		return false;
	}
	std::cout << C_RESET;

	return true;
}

bool cmdSelect(const std::vector<int>& command)
{
	ItemLocation loc;
	if (!parseLocStr(loc, command, 1))
		return false;

	File::Get().selected = loc;

	std::cout << C_CYAN;
	viewElement(loc.category, loc.element);
	std::cout << "-------------------------------------------\n\n" << C_RESET;

	return true;
}

bool cmdView(const std::vector<int>& command)
{
	ItemLocation loc;
	if (!parseLocStr(loc, command, 1))
		return false;

	std::cout << C_CYAN;

	if (loc.article == -2)
		viewElement(loc.category, loc.element);
	else
		viewArticle(loc.category, loc.element, loc.article);

	std::cout << "\n-------------------------------------------\n\n" << C_RESET;

	return true;
}