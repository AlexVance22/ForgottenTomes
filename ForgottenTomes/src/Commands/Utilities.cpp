#include "PCH.h"
#include "Utilities.h"

#include "core/Macros.h"
#include "files/File.h"

#include "Helpers.h"
#include "Parsing.h"


void viewCategory(size_t cIndex)
{
	switch (cIndex)
	{
	case 0:
		std::cout << "Sessions----------------------------------\n\n";
		break;
	case 1:
		std::cout << "Locations---------------------------------\n\n";
		break;
	case 2:
		std::cout << "Characters--------------------------------\n\n";
		break;
	case 3:
		std::cout << "Items-------------------------------------\n\n";
		break;
	}

	for (size_t i = 0; i < File::Category(cIndex).size(); i++)
		std::cout << i << ": " << File::Category(cIndex)[i].name << std::endl;

	std::cout << "\n------------------------------------------\n\n";
}

void viewElement(size_t cIndex, int eIndex)
{
	const Element& e = File::Category(cIndex)[eIndex];
	std::cout << "Name: " << e.name << '\n';

	for (size_t i = 0; i < e.content.size(); i++)
	{
		std::cout << "\n------------------------------------------\n";
		std::cout << i << " - " << e.content[i] << ":" << "\n\n";
		std::string path = categoryPath(cIndex);
		printFile(path + e.name + '/' + e.content[i] + ".txt");
	}
}

void viewArticle(size_t cIndex, int eIndex, int aIndex)
{
	const Element& e = File::Category(cIndex)[eIndex];

	std::cout << e.name + " article " << aIndex << ":\n\n";
	std::cout << e.content[aIndex] + "\n\n";
	std::string path = categoryPath(cIndex);
	printFile(path + e.name + '/' + e.content[aIndex] + ".txt");
}


void cmdList(const std::vector<Argument>& command)
{
	std::cout << C_CYAN;
	viewCategory((size_t)command[1].numerical);
	std::cout << C_RESET;
}

bool cmdSelect(const std::vector<Argument>& command)
{
	ItemLocation loc;
	if (!parseLocStr(loc, command, 1))
		return false;

	File::Get().selected = loc;

	std::cout << C_CYAN;
	viewElement(loc.category, loc.element);
	std::cout << "------------------------------------------\n\n" << C_RESET;

	return true;
}

bool cmdView(const std::vector<Argument>& command)
{
	ItemLocation loc;
	if (!parseLocStr(loc, command, 1))
		return false;

	std::cout << C_CYAN;

	if (loc.article == -2)
		viewElement(loc.category, loc.element);
	else
		viewArticle(loc.category, loc.element, loc.article);

	std::cout << "\n------------------------------------------\n\n" << C_RESET;

	return true;
}