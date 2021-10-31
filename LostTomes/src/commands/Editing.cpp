#include "PCH.h"
#include "Editing.h"

#include "core/Macros.h"
#include "files/File.h"

#include "Helpers.h"
#include "Parsing.h"


static void valueElement(size_t cIndex, int eIndex)
{
	int rel = (int)File::Category(cIndex)[eIndex].relevance;

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

	File::Category(cIndex)[eIndex].relevance = (Element::Relevance)std::stoi(relstr);
}

static void renameElement(size_t cIndex, int eIndex)
{
	std::string path = categoryPath(cIndex);

	std::cout << C_YELLOW << "Old: " << File::Category(cIndex)[eIndex].name << C_RESET << "\nNew: ";
	std::cin.ignore(0);
	std::string name;
	std::getline(std::cin, name);

	std::filesystem::rename(path + File::Category(cIndex)[eIndex].name, path + name);
	File::Category(cIndex)[eIndex].name = name;
}

static void renameArticle(size_t cIndex, int eIndex, int aIndex)
{
	std::string path = categoryPath(cIndex);
	path += File::Category(cIndex)[eIndex].name + '/';

	std::cout << C_YELLOW << "Old: " << File::Article({ cIndex, eIndex, aIndex }) << C_RESET << "\nNew: ";
	std::cin.ignore(0);
	std::string name;
	std::getline(std::cin, name);

	std::filesystem::rename(path + File::Article({ cIndex, eIndex, aIndex }) + ".txt", path + name + ".txt");
	File::Category(cIndex)[eIndex].content[aIndex] = name;
}


bool cmdEdit(const std::vector<Argument>& command)
{
	ItemLocation loc;
	if (!parseLocStr(loc, command, 1))
		return false;

	if (command[command.size() - 1].numerical == "relevance"_hash)
	{
		valueElement(loc.category, loc.element);
		return true;
	}

	std::string path = '\"' + categoryPath(loc.category);
	path += File::Element(loc).name + '/' + File::Article(loc) + ".txt\"";

	system(path.c_str());

	return true;
}

bool cmdRename(const std::vector<Argument>& command)
{
	ItemLocation loc;
	if (!parseLocStr(loc, command, 1))
		return false;

	if (loc.article == -2)
		renameElement(loc.category, loc.element);
	else
		renameArticle(loc.category, loc.element, loc.article);

	return true;
}