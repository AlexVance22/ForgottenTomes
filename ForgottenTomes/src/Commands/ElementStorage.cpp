#include "PCH.h"
#include "ElementStorage.h"

#include "CoreMacros.h"

#include "Editing.h"
#include "Utilities.h"

#include "Files/File.h"
#include "CMDenums.h"
#include "Helpers.h"


static void addComp(size_t fIndex, int iIndex, int cIndex, bool doBrief = false)
{
	std::string path = File::Get().path;

	appendCategory(path, fIndex);

	Element& e = File::Get().elements[fIndex][iIndex];

	std::string name = doBrief ? "Brief" : "New Element" + std::to_string(e.content.size());

	if (cIndex == -1)
	{
		e.content.emplace_back(name);
		path += e.name + "/" + e.content[e.content.size() - 1] + ".txt";
	}
	else
	{
		e.content.emplace(e.content.begin() + cIndex, name);
		path += e.name + "/" + e.content[cIndex] + ".txt";
	}

	std::cout << C_GREEN;
	viewElement(fIndex, iIndex);
	std::cout << '\n' << C_RESET;

	std::ofstream stream(path);
}

static void delComp(size_t fIndex, int iIndex, int cIndex)
{
	std::string path = File::Get().path;

	appendCategory(path, fIndex);

	Element& e = File::Get().elements[fIndex][iIndex];

	if (cIndex == -1)
	{
		path += e.name + "/" + e.content[e.content.size() - 1] + ".txt";
		e.content.pop_back();
	}
	else
	{
		path += e.name + "/" + e.content[cIndex] + ".txt";
		e.content.erase(e.content.begin() + cIndex);
	}

	std::cout << C_RED;
	viewElement(fIndex, iIndex);
	std::cout << '\n' << C_RESET;

	std::remove(path.c_str());
}


static void addElement(size_t fIndex, int iIndex)
{
	std::string path = File::Get().path;

	appendCategory(path, fIndex);

	if (iIndex == -1)
	{
		const Element& e = File::Get().elements[fIndex].emplace_back(fIndex);
		path += e.name;
		addComp(fIndex, File::Get().elements[fIndex].size() - 1, -1, true);
	}
	else
	{
		const auto& e = File::Get().elements[fIndex].emplace(File::Get().elements[fIndex].begin() + iIndex, fIndex);
		path += e->name;
		addComp(fIndex, iIndex, -1, true);
	}

	std::filesystem::create_directories(path);
}

static void delElement(size_t fIndex, int iIndex)
{
	const auto& e = File::Get().elements[fIndex];
	std::string path;

	appendCategory(path, fIndex);

	if (iIndex == -1)
	{
		std::filesystem::remove(path + e[e.size() - 1].name);
		File::Get().elements[fIndex].pop_back();
	}
	else
	{
		std::filesystem::remove(path + e[iIndex].name);
		File::Get().elements[fIndex].erase(File::Get().elements[fIndex].begin() + iIndex);
	}
}


bool cmdAdd(const std::vector<int>& command)
{
	ItemLocation loc;
	if (!findItem(loc, command, 1))
		return false;

	if ((ARG)loc.elementIndex == ARG::BCK)
		loc.elementIndex = -1;
	if ((ARG)loc.componentIndex == ARG::BCK)
		loc.componentIndex = -1;

	if (loc.componentIndex == -2)
		addElement(loc.folderIndex, loc.elementIndex);
	else
		addComp(loc.folderIndex, loc.elementIndex, loc.componentIndex);

	std::cout << C_GREEN;
	listElements((ARG)command[1], ARG::DEF);
	std::cout << C_RESET;

	return true;
}

bool cmdDel(const std::vector<int>& command)
{
	ItemLocation loc;
	if (!findItem(loc, command, 1))
		return false;

	if ((ARG)loc.elementIndex == ARG::BCK)
		loc.elementIndex = -1;
	if ((ARG)loc.componentIndex == ARG::BCK)
		loc.componentIndex = -1;

	if (loc.componentIndex == -2)
		delElement(loc.folderIndex, loc.elementIndex);
	else
		delComp(loc.folderIndex, loc.elementIndex, loc.componentIndex);

	std::cout << C_RED;
	listElements((ARG)command[1], ARG::DEF);
	std::cout << C_RESET;

	return true;
}