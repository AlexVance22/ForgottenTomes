#include "PCH.h"
#include "Editing.h"

#include "CoreMacros.h"

#include "Files/File.h"
#include "CMDenums.h"
#include "Helpers.h"


static void valueElement(size_t fIndex, size_t iIndex)
{
	int rel = (int)File::Get().elements[fIndex][iIndex].relevance;

	std::cout << C_YELLOW << "Old: ";
		
	if (rel == -1)
		std::cout << "undefined (-1)";
	else
	{
		std::cout << '[';
		for (int i = 0; i < 5; i++)
		{
			if (i < rel)
				std::cout << '*';
			else
				std::cout << ' ';
		}
		std::cout << ']';
	}

	std::cout << C_RESET << "\nNew: ";

	std::string relstr;
	std::cin.ignore(0);
	std::getline(std::cin, relstr);

	File::Get().elements[fIndex][iIndex].relevance = (Element::Relevance)std::stoi(relstr);
}

static void renameElement(size_t fIndex, size_t iIndex)
{
	std::string name;

	std::cout << C_YELLOW << "Old: " << File::Get().elements[fIndex][iIndex].name << C_RESET << "\nNew: ";
	std::cin.ignore(0);
	std::getline(std::cin, name);
	std::string base = File::Get().path;

	appendCategory(base, fIndex);

	std::filesystem::rename(base + File::Get().elements[fIndex][iIndex].name, base + name);
	File::Get().elements[fIndex][iIndex].name = name;
}

static void renameComponent(size_t fIndex, size_t iIndex, size_t cIndex)
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
}


bool cmdEdit(const std::vector<int>& command)
{
	ItemLocation loc;

	if ((ARG)command[command.size() - 1] == ARG::REL)
	{
		if (!findItem(loc, command, 1))
			return false;

		valueElement(loc.folderIndex, loc.elementIndex);
		return true;
	}

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