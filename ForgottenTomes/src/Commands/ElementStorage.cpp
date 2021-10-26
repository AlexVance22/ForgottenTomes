#include "PCH.h"
#include "ElementStorage.h"

#include "CoreMacros.h"
#include "CMDenums.h"

#include "Files/File.h"
#include "Utilities.h"
#include "Helpers.h"


static void addArticle(size_t cIndex, int eIndex, int aIndex)
{
	std::string path = categoryPath(cIndex);
	Element& e = File::Category(cIndex)[eIndex];
	path += e.name + '/';

	if (aIndex == -1)
		aIndex = e.content.size();

	std::string name = e.content.size() == 0 ? "Brief" : "Article_" + std::to_string(e.content.size());
	e.content.emplace(e.content.begin() + aIndex, name);
	path += e.content[aIndex] + ".txt";

	std::cout << C_GREEN;
	viewElement(cIndex, eIndex);
	std::cout << '\n' << C_RESET;

	std::ofstream stream(path);
}

static void delArticle(size_t cIndex, int eIndex, int aIndex)
{
	std::string path = categoryPath(cIndex);
	Element& e = File::Category(cIndex)[eIndex];

	if (aIndex == -1)
		aIndex = e.content.size() - 1;

	path += e.name + "/" + e.content[aIndex] + ".txt";
	e.content.erase(e.content.begin() + aIndex);

	std::cout << C_RED;
	viewElement(cIndex, eIndex);
	std::cout << '\n' << C_RESET;

	std::remove(path.c_str());
}


static void addElement(size_t cIndex, int eIndex)
{
	auto& category = File::Category(cIndex);

	if (eIndex == -1)
		eIndex = category.size();

	const Element& e = *category.emplace(category.begin() + eIndex, cIndex);
	std::filesystem::create_directories(categoryPath(cIndex) + e.name);
	addArticle(cIndex, eIndex, 0);
}

static void delElement(size_t cIndex, int eIndex)
{
	auto& category = File::Category(cIndex);

	if (eIndex == -1)
		eIndex = category.size() - 1;

	std::filesystem::remove_all(categoryPath(cIndex) + category[eIndex].name);
	category.erase(category.begin() + eIndex);
}


bool cmdAdd(const std::vector<int>& command)
{
	ItemLocation loc;
	if (!parseLocStr(loc, command, 1))
		return false;

	if (loc.article == -2)
		addElement(loc.category, loc.element);
	else
		addArticle(loc.category, loc.element, loc.article);

	std::cout << C_GREEN;
	listElements((ARG)command[1]);
	std::cout << C_RESET << '\n';

	return true;
}

bool cmdDel(const std::vector<int>& command)
{
	ItemLocation loc;
	if (!parseLocStr(loc, command, 1))
		return false;

	if (loc.article == -2)
		delElement(loc.category, loc.element);
	else
		delArticle(loc.category, loc.element, loc.article);

	std::cout << C_RED;
	listElements((ARG)command[1]);
	std::cout << C_RESET << '\n';

	return true;
}