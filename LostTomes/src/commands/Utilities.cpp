#include "PCH.h"
#include "Utilities.h"

#include "core/Exceptions.h"
#include "core/Macros.h"
#include "files/File.h"

#include "Helpers.h"
#include "Parsing.h"


void viewCategory(const ItemLocation& loc)
{
	switch (loc.category)
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

	const auto& category = File::Category(loc.category);

	for (size_t i = 0; i < category.size(); i++)
		std::cout << i << ": " << category[i].name << '\n';

	std::cout << "\n------------------------------------------\n\n";
}

void viewElement(const ItemLocation& loc)
{
	const Element& e = File::Element(loc);
	const fs::path pathbase = categoryPath(loc.category) / e.name;
	std::cout << "Name: " << e.name << '\n';

	for (size_t i = 0; i < e.content.size(); i++)
	{
		std::cout << "\n------------------------------------------\n";
		std::cout << i << " - " << e.content[i] << ":\n\n";
		printFile(pathbase / (e.content[i] + ".txt"));
	}
}

void viewArticle(const ItemLocation& loc)
{
	const Element& e = File::Element(loc);

	std::cout << e.name + " article " << loc.article << ":\n\n";
	std::cout << e.content[loc.article] + "\n\n";
	fs::path path = categoryPath(loc.article);
	printFile(path / e.name / (e.content[loc.article] + ".txt"));
}


void cmdList(const std::vector<Argument>& command)
{
	if (command.size() == 1)
		throw InvalidCategory("category argument required");

	std::cout << C_CYAN;
	viewCategory({ (size_t)command[1].numerical, 0, 0 });
	std::cout << C_RESET;
}

void cmdSelect(const std::vector<Argument>& command)
{
	if (command.size() == 1)
	{
		const auto sel = File::Selected();
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

		return;
	}

	if (command.size() == 2)
	{
		if (command[1].type != Argument::Type::Special && command[1].numerical != 2)
			throw InvalidArgument("location not found");
	
		File::Get().selected.category = 4;
		File::Get().selected.element = -1;
		File::Get().selected.article = -2;

		std::ifstream istream("res/startup.json");
		if (!istream.is_open())
			throw FileNotFound("unable to open startup file");

		nlohmann::json j;
		istream >> j;
		istream.close();
		j["selected"] = nullptr;

		std::ofstream ostream("res/startup.json", std::ios::trunc);
		if (!ostream.is_open())
			throw FileNotFound("unable to open startup file");

		ostream << j;
		ostream.close();

		return;
	}

	const ItemLocation loc = parseLocStr(command, 1);

	File::Get().selected = loc;

	std::cout << C_CYAN;
	viewElement(loc);
	std::cout << "\n------------------------------------------\n\n" << C_RESET;

	std::ifstream istream("res/startup.json");
	if (!istream.is_open())
		throw FileNotFound("unable to open startup file");

	nlohmann::json j;
	istream >> j;
	istream.close();
	if (loc.element == -1)
		j["selected"] = nullptr;
	else
	{
		j["selected"]["category"] = loc.category;
		j["selected"]["element"] = loc.element;
	}

	std::ofstream ostream("res/startup.json", std::ios::trunc);
	if (!ostream.is_open())
		throw FileNotFound("unable to open startup file");

	ostream << j;
	ostream.close();
}

void cmdView(const std::vector<Argument>& command)
{
	const ItemLocation loc = parseLocStr(command, 1);

	std::cout << C_CYAN;

	if (loc.article == -2)
		viewElement(loc);
	else
		viewArticle(loc);

	std::cout << "\n\n------------------------------------------\n\n" << C_RESET;
}