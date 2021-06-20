#include "PCH.h"

#include "CoreMacros.h"

#include "Helpers.h"


static bool getSelected(ItemLocation& loc)
{
	if (File::Selected().folderIndex != -1 && File::Selected().elementIndex != -1)
	{
		loc = File::Selected();
		return true;
	}
	
	LOG_ERROR("no item selected");

	return false;
}


bool findItem(ItemLocation& loc, const std::vector<int>& command, size_t startIndex)
{
	bool current = false;;

	switch ((ARG)command[startIndex])
	{
	case ARG::CRN:
		if (getSelected(loc))
			current = true;
		else
			return false;

		break;

	case ARG::SES: loc.folderIndex = 0;
		break;
	case ARG::LOC: loc.folderIndex = 1;
		break;
	case ARG::CHA: loc.folderIndex = 2;
		break;
	case ARG::ITM: loc.folderIndex = 3;
		break;

	default:
		LOG_ERROR("invalid item type");
		return false;
	}

	if (!current)
	{
		if (command[startIndex] < (int)File::Get().elements[loc.folderIndex].size())
			loc.elementIndex = command[startIndex + 1];
		else
		{
			LOG_ERROR("invalid item index");
			return false;
		}
	}

	if (command.size() == startIndex + 4 - current && (ARG)command[startIndex + 2 - current] == ARG::CMP)
	{
		if (command[startIndex + 3 - current] < (int)File::Get().elements[loc.folderIndex][loc.elementIndex].content.size())
			loc.componentIndex = command[startIndex + 3 - current];
		else
		{
			LOG_ERROR("invalid article index");
			return false;
		}
	}

	return true;
}


void appendCategory(std::string& base, size_t fIndex)
{
	switch (fIndex)
	{
	case 0: base += "\\sessions\\";
		break;
	case 1: base += "\\locations\\";
		break;
	case 2: base += "\\characters\\";
		break;
	case 3: base += "\\items\\";
		break;
	}
}


void printFile(const std::string& fileName)
{
	std::ifstream stream(fileName);
	if (stream.is_open())
	{
		std::string line;
		while (std::getline(stream, line))
			std::cout << line << std::endl;
	}
}


bool listElements(ARG code)
{
	int group;

	switch (code)
	{
	case ARG::SES:
		std::cout << "Sessions----------------------------------\n\n";
		group = 0;
		break;
	case ARG::LOC:
		std::cout << "Locations---------------------------------\n\n";
		group = 1;
		break;
	case ARG::CHA:
		std::cout << "Characters--------------------------------\n\n";
		group = 2;
		break;
	case ARG::ITM:
		std::cout << "Characters--------------------------------\n\n";
		group = 3;
		break;
	default:
		return false;
	}

	for (size_t i = 0; i < File::Get().elements[group].size(); i++)
		std::cout << i << ": " << File::Get().elements[group][i].name << std::endl;

	std::cout << "\n------------------------------------------\n\n";

	return true;
}