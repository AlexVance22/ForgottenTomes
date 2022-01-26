#include "PCH.h"
#include "ElementStorage.h"

#include "core/Exceptions.h"
#include "core/Macros.h"
#include "files/File.h"

#include "Utilities.h"
#include "Helpers.h"
#include "Parsing.h"

#include "core/Profiler.h"


static void addArticle(const ItemLocation& loc)
{
	Element& e = File::Element(loc);
	fs::path path = categoryPath(loc.category) / e.name;

	const auto article = (loc.article == -1) ? e.content.size() - 1 : loc.article;

	const std::string name = e.content.size() == 0 ? "Brief" : "Article_" + std::to_string(e.content.size());
	e.content.emplace(e.content.begin() + article, name);
	path /= e.content[article] + ".txt";

	std::cout << C_GREEN;
	viewElement(loc);
	std::cout << C_RESET << '\n';

	std::ofstream stream(path);
}

static void delArticle(const ItemLocation& loc)
{
	Element& e = File::Element(loc);

	const auto article = (loc.article == -1) ? e.content.size() - 1 : loc.article;

	const fs::path path = categoryPath(loc.article) / e.name / (e.content[article] + ".txt");
	e.content.erase(e.content.begin() + article);

	std::cout << C_RED;
	viewElement(loc);
	std::cout << C_RESET << '\n';

	std::remove(path.generic_string().c_str());
}


static void addElement(const ItemLocation& loc)
{
	const fs::path path = categoryPath(loc.category);
	auto& category = File::Category(loc.category);

	auto element = (loc.element == -1) ? category.size() : loc.element;

	Element& e = *category.emplace(category.begin() + loc.element, loc.category, category.size());
	e.content.emplace_back("Brief");

	std::filesystem::create_directories(path / e.name);
	std::ofstream stream(path / e.name / "Brief.txt");

	std::cout << C_GREEN;
	viewCategory(loc);
	std::cout << C_RESET;
}

static void delElement(const ItemLocation& loc)
{
	auto& category = File::Category(loc.category);

	const auto element = (loc.element == -1) ? category.size() - 1 : loc.element;

	std::filesystem::remove_all(categoryPath(loc.category) / category[element].name);
	category.erase(category.begin() + element);

	std::cout << C_RED;
	viewCategory(loc);
	std::cout << C_RESET;
}


void cmdAdd(const std::vector<Argument>& command)
{
	const ItemLocation loc = parseLocStr(command, 1);

	if (loc.article == -2)
		addElement(loc);
	else
		addArticle(loc);
}

void cmdDel(const std::vector<Argument>& command)
{
	const ItemLocation loc = parseLocStr(command, 1);

	if (loc.article == -2)
		delElement(loc);
	else
		delArticle(loc);
}