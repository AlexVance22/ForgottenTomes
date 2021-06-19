#include "PCH.h"

#include "ElementStorage.h"
#include "Editing.h"

#include "Files/File.h"
#include "CMDenums.h"
#include "Helpers.h"


static bool addComp(size_t fIndex, int iIndex, int cIndex, bool doBrief = false)
{
	if (iIndex >= (int)File::Get().elements[fIndex].size())
	{
		std::cout << "---\nERROR: invalid element index\n---\n" << std::endl;
		return false;
	}

	Element& e = File::Get().elements[fIndex][iIndex];
	if (cIndex < (int)e.content.size())
	{
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

		std::string name;

		if (doBrief)
			name = "Brief";
		else
			name = "New Element" + std::to_string(e.content.size());

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

		std::ofstream stream(path);
		return true;
	}

	std::cout << "---\nERROR: invalid article index\n---\n" << std::endl;
	return false;
}

static bool delComp(size_t fIndex, int iIndex, int cIndex)
{
	if (iIndex >= (int)File::Get().elements[fIndex].size())
	{
		std::cout << "---\nERROR: invalid element index\n---\n" << std::endl;
		return false;
	}

	Element& e = File::Get().elements[fIndex][iIndex];
	if (cIndex < (int)e.content.size())
	{
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

		std::remove(path.c_str());
		return true;
	}

	std::cout << "---\nERROR: invalid article index\n---\n" << std::endl;
	return false;
}


static bool addElement(size_t fIndex, int iIndex)
{
	if (iIndex < (int)File::Get().elements[fIndex].size())
	{
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

		if (iIndex == -1)
		{
			const Element& e = File::Get().elements[fIndex].emplace_back();
			path += e.name;
			addComp(fIndex, File::Get().elements[fIndex].size() - 1, -1, true);
		}
		else
		{
			const auto& e = File::Get().elements[fIndex].emplace(File::Get().elements[fIndex].begin() + iIndex);
			path += e->name;
			addComp(fIndex, iIndex, -1, true);
		}

		std::filesystem::create_directories(path);
		return true;
	}

	std::cout << "---\nERROR: invalid element index\n---\n" << std::endl;
	return false;
}

static bool delElement(size_t fIndex, int iIndex)
{
	if (iIndex < (int)File::Get().elements[fIndex].size())
	{
		const auto& e = File::Get().elements[fIndex];
		std::string path;

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

		return true;
	}

	std::cout << "---\nERROR: invalid element index\n---\n" << std::endl;
	return false;
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

	if (loc.componentIndex != -2)
	{
		if (!addComp(loc.folderIndex, loc.elementIndex, loc.componentIndex))
			return false;
	}
	else if (!addElement(loc.folderIndex, loc.elementIndex))
		return false;

	listElements((ARG)command[1]);

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

	if (loc.componentIndex != -2)
	{
		if (!delComp(loc.folderIndex, loc.elementIndex, loc.componentIndex))
			return false;
	}
	else if (!delElement(loc.folderIndex, loc.elementIndex))
		return false;

	listElements((ARG)command[1]);

	return true;
}