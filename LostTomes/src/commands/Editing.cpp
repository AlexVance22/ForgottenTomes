#include "PCH.h"
#include "Editing.h"

#include "core/Macros.h"
#include "files/File.h"

#include "Helpers.h"
#include "Parsing.h"


static void valueElement(const ItemLocation& loc)
{
	const int rel = (int)File::Category(loc.category)[loc.element].relevance;

	std::cout << C_YELLOW << "Old: ";
		
	if (rel == -1)
		std::cout << "undefined (-1)";
	else
	{
		std::cout << '[';
		for (int i = 0; i < 5; i++)
		{
			if (i < rel)
				std::cout << '*';
			else
				std::cout << ' ';
		}
		std::cout << ']';
	}

	std::cout << C_RESET << "\nNew: ";

	std::string relstr;
	std::cin.ignore(0);
	std::getline(std::cin, relstr);

	File::Element(loc).relevance = (Element::Relevance)std::stoi(relstr);
}

static void renameElement(const ItemLocation& loc)
{
	const fs::path path = categoryPath(loc.category);

	std::cout << C_YELLOW << "Old: " << File::Element(loc).name << C_RESET << "\nNew: ";
	std::cin.ignore(0);
	std::string name;
	std::getline(std::cin, name);

	std::filesystem::rename(path / File::Element(loc).name, path / name);
	File::Element(loc).name = name;
}

static void renameArticle(const ItemLocation& loc)
{
	const fs::path path = categoryPath(loc.category) / File::Element(loc).name;

	std::cout << C_YELLOW << "Old: " << File::Article(loc) << C_RESET << "\nNew: ";
	std::cin.ignore(0);
	std::string name;
	std::getline(std::cin, name);

	std::filesystem::rename(path / (File::Article(loc) + ".txt"), path / (name + ".txt"));
	File::Element(loc).content[loc.article] = name;
}


void cmdEdit(const std::vector<Argument>& command)
{
	const ItemLocation loc = parseLocStr(command, 1);

	if (command[command.size() - 1].numerical == "relevance"_hash)
	{
		valueElement(loc);
		return;
	}

	const fs::path path = categoryPath(loc.category) / File::Element(loc).name / (File::Article(loc) + ".txt");

	system(("\"" + path.generic_string() + "\"").c_str());
}

void cmdRename(const std::vector<Argument>& command)
{
	const ItemLocation loc = parseLocStr(command, 1);

	if (loc.article == -2)
		renameElement(loc);
	else
		renameArticle(loc);
}