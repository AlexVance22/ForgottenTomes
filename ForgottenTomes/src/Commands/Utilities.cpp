#include "PCH.h"

#include "Utilities.h"

#include "Files/File.h"
#include "CMDenums.h"
#include "Helpers.h"


static void viewElement(int fIndex, int iIndex)
{
	const Element& e = File::Get().elements[fIndex][iIndex];

	std::cout << "Name: " << e.name << "\n\n";

	for (size_t i = 0; i < e.content.size(); i++)
	{
		std::cout << "------------\n";

		std::cout << i << " - " << e.content[i] << ":" << "\n\n";
		std::string path = File::Get().path;

		switch (fIndex)
		{
		case 0: path += "\\sessions\\";
			break;
		case 1: path += "\\locations\\";
			break;
		case 2: path += "\\characters\\";
			break;
		case 3: path += "\\items\\";
			break;
		}

		printFile(path + e.name + '\\' + e.content[i] + ".txt");
	}
}

static void viewComponent(int fIndex, int iIndex, int cIndex)
{
	const Element& e = File::Get().elements[fIndex][iIndex];

	std::cout << e.name + " article " << cIndex << ":\n\n";
	std::cout << e.content[cIndex] + "\n\n";

	std::string path = File::Get().path;

	switch (fIndex)
	{
	case 0:
		path += "\\sessions\\";
		break;
	case 1:
		path += "\\locations\\";
		break;
	case 2:
		path += "\\characters\\";
		break;
	case 3:
		path += "\\items\\";
		break;
	}

	printFile(path + e.name + '\\' + e.content[cIndex] + ".txt");
}


bool cmdList(const std::vector<int>& command)
{
	if (!listElements((ARG)command[1]))
	{
		std::cout << "---\nERROR: invalid element type\n---" << std::endl;
		return false;
	}

	return true;
}

bool cmdSelect(const std::vector<int>& command)
{
	ItemLocation loc;
	if (!findItem(loc, command, 1))
		return false;

	File::Selected() = loc;

	viewElement(loc.folderIndex, loc.elementIndex);

	std::cout << "-------------------------------------------\n" << std::endl;

	return true;
}

bool cmdView(const std::vector<int>& command)
{
	ItemLocation loc;
	if (!findItem(loc, command, 1))
		return false;

	if (loc.componentIndex != -2)
		viewElement(loc.folderIndex, loc.elementIndex);
	else
		viewComponent(loc.folderIndex, loc.elementIndex, loc.componentIndex);

	std::cout << "-------------------------------------------\n" << std::endl;

	return true;
}