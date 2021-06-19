#include "PCH.h"

#include "Helpers.h"


bool findItem(ItemLocation& loc, const std::vector<int>& command, size_t startIndex)
{
	bool current = false;;

	switch ((ARG)command[startIndex])
	{
	case ARG::CRN:
		if (File::Selected().folderIndex != -1 && File::Selected().elementIndex != -1)
		{
			loc = File::Selected();
			current = true;
		}
		else
		{
			std::cout << "---\nERROR: no item selected\n---\n";
			return false;
		}
		break;

	case ARG::SES:
		loc.folderIndex = 0;
		loc.elementIndex = command[startIndex + 1];
		break;
	case ARG::LOC:
		loc.folderIndex = 1;
		loc.elementIndex = command[startIndex + 1];
		break;
	case ARG::CHA:
		loc.folderIndex = 2;
		loc.elementIndex = command[startIndex + 1];
		break;
	case ARG::ITM:
		loc.folderIndex = 3;
		loc.elementIndex = command[startIndex + 1];
		break;

	default:
		std::cout << "---\nERROR: invalid access mode\n---\n";
		return false;
	}

	if (command.size() == startIndex + 4 - current && (ARG)command[startIndex + 2 - current] == ARG::CMP)
		loc.componentIndex = command[startIndex + 3 - current];

	return true;
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