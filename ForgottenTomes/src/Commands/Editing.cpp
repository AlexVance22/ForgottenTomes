#include "PCH.h"
#include "Editing.h"

#include "CoreMacros.h"

#include "Files/File.h"
#include "CMDenums.h"
#include "Helpers.h"


bool renameElement(size_t fIndex, size_t iIndex)
{
	std::string name;

	std::cout << C_YELLOW << "Old: " << File::Get().elements[fIndex][iIndex].name << C_RESET << "\nNew: ";
	std::cin.ignore(0);
	std::getline(std::cin, name);
	std::string base = File::Get().path;

	appendCategory(base, fIndex);

	std::filesystem::rename(base + File::Get().elements[fIndex][iIndex].name, base + name);
	File::Get().elements[fIndex][iIndex].name = name;

	return true;
}

bool renameComponent(size_t fIndex, size_t iIndex, size_t cIndex)
{
	std::string name;

	std::cout << C_YELLOW << "Old: " << File::Get().elements[fIndex][iIndex].content[cIndex] << C_RESET << "\nNew: ";
	std::cin.ignore(0);
	std::getline(std::cin, name);
	std::string base = File::Get().path;

	appendCategory(base, fIndex);

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

	appendCategory(path, loc.folderIndex);

	path += File::Get().elements[loc.folderIndex][loc.elementIndex].name + '\\' + File::Get().elements[loc.folderIndex][loc.elementIndex].content[loc.componentIndex];

	system((std::string("notepad.exe ") + path).c_str());

	return true;
}

bool cmdRename(const std::vector<int>& command)
{
	ItemLocation loc;
	if (!findItem(loc, command, 1))
		return false;

	if (loc.componentIndex == -2)
		renameElement(loc.folderIndex, loc.elementIndex);
	else
		renameComponent(loc.folderIndex, loc.elementIndex, loc.componentIndex);

	return true;
}