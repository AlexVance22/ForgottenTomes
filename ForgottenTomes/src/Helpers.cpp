#include "PCH.h"
#include "Helpers.h"

#include "Files/File.h"
#include "CoreMacros.h"


bool parseLocStr(ItemLocation& loc, const std::vector<int>& command, size_t idx)
{
	bool current = false;

	switch ((ARG)command[idx])
	{
	case ARG::CRN:
		if (File::IsSelected())
		{
			loc = File::Selected().value();
			current = true;
			break;
		}
		else
			return false;
	case ARG::SES:
		loc.category = 0;
		break;
	case ARG::LOC:
		loc.category = 1;
		break;
	case ARG::CHA:
		loc.category = 2;
		break;
	case ARG::ITM:
		loc.category = 3;
		break;
	default:
		LOG_ERROR("invalid item type");
		return false;
	}

	idx++;

	if (!current)
	{
		if ((ARG)command[idx] == ARG::BCK)
			loc.element = -1;
		else
			loc.element = command[idx];
		idx++;
	}

	if (idx < command.size())
	{
		if ((ARG)command[idx++] == ARG::CMP)
		{
			if ((ARG)command[idx] == ARG::BCK)
				loc.article = -1;
			else
				loc.article = command[idx];
			return true;
		}
		
		LOG_ERROR("invalid trailing arguments");
		return false;
	}
	
	loc.article = -2;
	return true;
}

std::string categoryPath(size_t cIndex)
{
	std::string path = File::Get().rootdir;
	switch (cIndex)
	{
	case 0: path += "/sessions/";
		break;
	case 1: path += "/locations/";
		break;
	case 2: path += "/characters/";
		break;
	case 3: path += "/items/";
		break;
	}
	return path;
}

void printFile(const std::string& filepath)
{
	std::ifstream stream(filepath);
	if (stream.is_open())
		for (std::string line; std::getline(stream, line); std::cout << line << '\n');
}

bool listElements(ARG code)
{
	uint32_t category;

	switch (code)
	{
	case ARG::SES: category = 0;
		std::cout << "Sessions----------------------------------\n\n";
		break;
	case ARG::LOC: category = 1;
		std::cout << "Locations---------------------------------\n\n";
		break;
	case ARG::CHA: category = 2;
		std::cout << "Characters--------------------------------\n\n";
		break;
	case ARG::ITM: category = 3;
		std::cout << "Items-------------------------------------\n\n";
		break;
	default:
		return false;
	}

	for (size_t i = 0; i < File::Category(category).size(); i++)
		std::cout << i << ": " << File::Category(category)[i].name << std::endl;

	std::cout << "\n------------------------------------------\n\n";

	return true;
}