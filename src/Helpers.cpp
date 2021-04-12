#include "PCH.h"

#include "Helpers.h"

#include "File.h"


bool findItem(ItemLocation& loc, const std::vector<int>& command, size_t startIndex)
{
	bool current = false;;

	switch ((ARG)command[startIndex])
	{
	case ARG::CRN:
		if (File::Get().vfs.folderIndex != -1 && File::Get().vfs.itemIndex != -1)
		{
			loc.folderIndex = File::Get().vfs.folderIndex;
			loc.elementIndex = File::Get().vfs.itemIndex;
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

	default:
		std::cout << "---\nERROR: invalid access mode\n---\n";
		return false;
	}

	if (command.size() == startIndex + 4 - current && (ARG)command[startIndex + 2 - current] == ARG::CMP)
		loc.componentIndex = command[startIndex + 3 - current];

	return true;
}


bool listElements(ARG code)
{
	switch (code)
	{
	case ARG::SES:
		std::cout << "Sessions----------------------------------\n\n";

		for (size_t i = 0; i < File::Get().sessions.size(); i++)
			std::cout << i << ": " << File::Get().sessions[i].name << std::endl;

		break;
	case ARG::LOC:
		std::cout << "Locations---------------------------------\n\n";

		for (size_t i = 0; i < File::Get().characters.size(); i++)
			std::cout << i << ": " << File::Get().characters[i].name << std::endl;

		break;
	case ARG::CHA:
		std::cout << "Characters--------------------------------\n\n";

		for (size_t i = 0; i < File::Get().characters.size(); i++)
			std::cout << i << ": " << File::Get().characters[i].name << std::endl;

		break;
	default:
		return false;
	}

	std::cout << "\n------------------------------------------\n\n";

	return true;
}