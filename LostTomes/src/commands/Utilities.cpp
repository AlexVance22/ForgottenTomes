#include "PCH.h"
#include "Utilities.h"

#include "core/Macros.h"
#include "files/File.h"

#include "Helpers.h"
#include "Parsing.h"


static bool StartupEditLoc(const std::string& filepath, const std::string& key, ItemLocation loc)
{
	std::ifstream istream("res/startup.json");
	if (istream.is_open())
	{
		nlohmann::json j;
		istream >> j;
		istream.close();
		if (loc.element == -1)
			j[key] = nullptr;
		else
		{
			j[key]["category"] = loc.category;
			j[key]["element"] = loc.element;
		}

		std::ofstream ostream("res/startup.json", std::ios::trunc);
		if (ostream.is_open())
		{
			ostream << j;
			ostream.close();
			return true;
		}
	}
	return false;
}


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

	const auto& category = File::Category(cIndex);

	for (size_t i = 0; i < category.size(); i++)
		std::cout << i << ": " << category[i].name << '\n';

	std::cout << "\n------------------------------------------\n\n";
}

void viewElement(size_t cIndex, int eIndex)
{
	const Element& e = File::Category(cIndex)[eIndex];
	std::string pathbase = categoryPath(cIndex) + e.name + '/';
	std::cout << "Name: " << e.name << '\n';

	for (size_t i = 0; i < e.content.size(); i++)
	{
		std::cout << "\n------------------------------------------\n";
		std::cout << i << " - " << e.content[i] << ":\n\n";
		printFile(pathbase + e.content[i] + ".txt");
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
	if (command.size() == 1)
	{
		LOG_ERROR("category argument required");
		return;
	}

	std::cout << C_CYAN;
	viewCategory((size_t)command[1].numerical);
	std::cout << C_RESET;
}

bool cmdSelect(const std::vector<Argument>& command)
{
	if (command.size() == 1)
	{
		auto sel = File::Selected();
		if (sel)
		{
			switch (sel.value().category)
			{
			case 0:
				std::cout << "Session ";
				break;
			case 1:
				std::cout << "Location ";
				break;
			case 2:
				std::cout << "Character ";
				break;
			case 3:
				std::cout << "Item ";
				break;
			}
			std::cout << sel.value().element << " -> " << File::Element(sel.value()).name << "\n\n";
		}
		else
			std::cout << "No element selected\n\n";

		return true;
	}

	if (command.size() == 2)
	{
		if (command[1].type != Argument::Type::Special && command[1].numerical != 2)
		{
			LOG_ERROR("location not found");
			return false;
		}
		File::Get().selected.category = 4;
		File::Get().selected.element = -1;
		File::Get().selected.article = -2;

		if (!StartupEditLoc("res/startup.json", "selected", ItemLocation()))
			return false;

		return true;
	}

	ItemLocation loc;
	if (!parseLocStr(loc, command, 1))
		return false;

	File::Get().selected = loc;

	std::cout << C_CYAN;
	viewElement(loc.category, loc.element);
	std::cout << "\n------------------------------------------\n\n" << C_RESET;

	if (!StartupEditLoc("res/startup.json", "selected", loc))
		return false;

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

	std::cout << "\n\n------------------------------------------\n\n" << C_RESET;

	return true;
}