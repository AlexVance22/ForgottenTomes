#include "PCH.h"

#include "Editing.h"

#include "File.h"
#include "CMDenums.h"
#include "Helpers.h"


bool renameElement(size_t fIndex, size_t iIndex)
{
	std::string name;

	std::cout << "Old: ";

	switch (fIndex)
	{
	case 0: {
		std::cout << File::Get().sessions[iIndex].name << "\nNew: ";
		std::cin.ignore(0);
		std::getline(std::cin, name);

		std::string base = File::Get().path + "/sessions/";
		std::filesystem::rename(base + File::Get().sessions[iIndex].name, base + name);

		File::Get().sessions[iIndex].name = name;
		break; }
	case 1: {
		std::cout << File::Get().locations[iIndex].name << "\nNew: ";
		std::cin.ignore(0);
		std::getline(std::cin, name);

		std::string base = File::Get().path + "/locations/";
		std::filesystem::rename(base + File::Get().locations[iIndex].name, base + name);

		File::Get().locations[iIndex].name = name;
		break; }
	case 2: {
		std::cout << File::Get().characters[iIndex].name << "\nNew: ";
		std::cin.ignore(0);
		std::getline(std::cin, name);

		std::string base = File::Get().path + "/characters/";
		std::filesystem::rename(base + File::Get().characters[iIndex].name, base + name);

		File::Get().characters[iIndex].name = name;
		break; }
	}

	return true;
}

bool renameComponent(size_t fIndex, size_t iIndex, size_t cIndex)
{
	std::string name;

	std::cout << "Old: ";

	switch (fIndex)
	{
	case 0: {
		std::cout << File::Get().sessions[iIndex].elems[cIndex] << "\nNew: ";
		std::cin.ignore(0);
		std::getline(std::cin, name);

		std::string base = File::Get().path + "\\sessions\\" + File::Get().sessions[iIndex].name + '\\';
		std::filesystem::rename(base + File::Get().sessions[iIndex].elems[cIndex] + ".txt", base + name + ".txt");

		File::Get().sessions[iIndex].elems[cIndex] = name;
		break; }
	case 1: {
		std::cout << File::Get().locations[iIndex].prehistory[cIndex] << "\nNew: ";
		std::cin.ignore(0);
		std::getline(std::cin, name);

		std::string base = File::Get().path + "/locations/" + File::Get().locations[iIndex].name + '/';
		std::filesystem::rename(base + File::Get().locations[iIndex].prehistory[cIndex], base + ".txt" + name + ".txt");

		File::Get().locations[iIndex].prehistory[cIndex] = name;
		break; }
	case 2: {
		std::cout << File::Get().characters[iIndex].name << "\nNew: ";
		std::cin.ignore(0);
		std::getline(std::cin, name);

		std::string base = File::Get().path + "/characters/" + File::Get().characters[iIndex].name + '/';
		std::filesystem::rename(base + File::Get().characters[iIndex].backstory[cIndex] + ".txt", base + name + ".txt");

		File::Get().characters[iIndex].backstory[cIndex] = name;
		break; }
	}

	return true;
}


bool cmdEdit(const std::vector<int>& command)
{
	ItemLocation loc;
	if (!findItem(loc, command, 1))
		return false;

	std::string path;

	switch (loc.folderIndex)
	{
	case 0:
		path = File::Get().path + "/sessions/" + File::Get().sessions[loc.elementIndex].name
			+ "/" + File::Get().sessions[loc.elementIndex].elems[loc.componentIndex];
		break;
	case 1:
		path = File::Get().path + "/locations/" + File::Get().locations[loc.elementIndex].name
			+ "/" + File::Get().locations[loc.elementIndex].prehistory[loc.componentIndex];
		break;
	case 2:
		path = File::Get().path + "/character/" + File::Get().characters[loc.elementIndex].name
			+ "/" + File::Get().characters[loc.elementIndex].backstory[loc.componentIndex];
		break;
	}

	system(("notepad.exe " + path).c_str());

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