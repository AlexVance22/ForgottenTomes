#include "PCH.h"

#include "Editing.h"

#include "Files/File.h"
#include "CMDenums.h"
#include "Helpers.h"


static bool renameElement(size_t fIndex, size_t iIndex)
{
	std::string name;

	std::cout << "Old: " << File::Get().elements[fIndex][iIndex].name << "\nNew: ";
	std::cin.ignore(0);
	std::getline(std::cin, name);
	std::string base = File::Get().path;

	switch (fIndex)
	{
	case 0:
		base += "\\sessions\\";
		break;
	case 1:
		base += "\\locations\\";
		break;
	case 2:
		base += "\\characters\\";
		break;
	case 3:
		base += "\\items\\";
		break;
	}

	std::filesystem::rename(base + File::Get().elements[fIndex][iIndex].name, base + name);
	File::Get().elements[fIndex][iIndex].name = name;

	return true;
}

static bool renameComponent(size_t fIndex, size_t iIndex, size_t cIndex)
{
	std::string name;

	std::cout << "Old: " << File::Get().elements[fIndex][iIndex].content[cIndex] << "\nNew: ";
	std::cin.ignore(0);
	std::getline(std::cin, name);
	std::string base = File::Get().path;

	switch (fIndex)
	{
	case 0:
		base += "\\sessions\\";
		break;
	case 1:
		base += "\\locations\\";
		break;
	case 2:
		base += "\\characters\\";
		break;
	case 3:
		base += "\\items\\";
		break;
	}

	base += File::Get().elements[fIndex][iIndex].name + '\\';

	std::filesystem::rename(base + File::Get().elements[fIndex][iIndex].content[cIndex] + ".txt", base + name + ".txt");
	File::Get().elements[fIndex][iIndex].content[cIndex] = name;

	return true;
}


bool cmdEdit(const std::vector<int>& command)
{
	ItemLocation loc;
	if (!findItem(loc, command, 1))
		return false;

	std::string path = File::Get().path;

	switch (loc.folderIndex)
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

	path += File::Get().elements[loc.folderIndex][loc.elementIndex].name + '\\' + File::Get().elements[loc.folderIndex][loc.elementIndex].content[loc.componentIndex];

	system((std::string("notepad.exe ") + path).c_str());

	return true;
}

bool cmdRename(const std::vector<int>& command)
{
	ItemLocation loc;
	if (!findItem(loc, command, 1))
		return false;

	if (loc.componentIndex != -2)
		renameComponent(loc.folderIndex, loc.elementIndex, loc.componentIndex);
	else
		renameElement(loc.folderIndex, loc.elementIndex);

	return true;
}