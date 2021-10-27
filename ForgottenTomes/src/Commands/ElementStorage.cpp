#include "PCH.h"
#include "ElementStorage.h"

#include "core/Macros.h"
#include "files/File.h"

#include "Utilities.h"
#include "Helpers.h"
#include "Parsing.h"


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
	std::cout << C_RESET << '\n';

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
	std::cout << C_RESET << '\n';

	std::remove(path.c_str());
}


static void addElement(size_t cIndex, int eIndex)
{
	std::string path = categoryPath(cIndex);
	auto& category = File::Category(cIndex);

	if (eIndex == -1)
		eIndex = category.size();

	Element& e = *category.emplace(category.begin() + eIndex, cIndex);
	e.content.emplace_back("Brief");

	std::filesystem::create_directories(path + e.name);
	std::ofstream stream(path + e.name + "/Brief.txt");

	std::cout << C_GREEN;
	viewCategory(cIndex);
	std::cout << C_RESET;
}

static void delElement(size_t cIndex, int eIndex)
{
	auto& category = File::Category(cIndex);

	if (eIndex == -1)
		eIndex = category.size() - 1;

	std::filesystem::remove_all(categoryPath(cIndex) + category[eIndex].name);
	category.erase(category.begin() + eIndex);

	std::cout << C_RED;
	viewCategory(cIndex);
	std::cout << C_RESET;
}


bool cmdAdd(const std::vector<Argument>& command)
{
	ItemLocation loc;
	if (!parseLocStr(loc, command, 1))
		return false;

	if (loc.article == -2)
		addElement(loc.category, loc.element);
	else
		addArticle(loc.category, loc.element, loc.article);

	return true;
}

bool cmdDel(const std::vector<Argument>& command)
{
	ItemLocation loc;
	if (!parseLocStr(loc, command, 1))
		return false;

	if (loc.article == -2)
		delElement(loc.category, loc.element);
	else
		delArticle(loc.category, loc.element, loc.article);

	return true;
}