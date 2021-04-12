#include "PCH.h"

#include "ElementStorage.h"

#include "File.h"
#include "CMDenums.h"
#include "Helpers.h"


bool addSession(int index)
{
	if (index == -1)
	{
		const Session& s = File::Get().sessions.emplace_back();
		std::filesystem::create_directories(File::Get().path + "/sessions/" + s.name);
		return true;
	}
	if (index < File::Get().sessions.size())
	{
		const auto& s = File::Get().sessions.emplace(File::Get().sessions.begin() + index);
		std::filesystem::create_directories(File::Get().path + "/sessions/" + s->name);
		return true;
	}
	
	std::cout << "---\nERROR: invalid element index\n---\n" << std::endl;
	return false;
}

bool addLocation(int index)
{
	if (index == -1)
	{
		const Location& l = File::Get().locations.emplace_back();
		std::filesystem::create_directories(File::Get().path + "/locations/" + l.name);
		return true;
	}
	if (index < File::Get().locations.size())
	{
		const auto& l = File::Get().locations.emplace(File::Get().locations.begin() + index);
		std::filesystem::create_directories(File::Get().path + "/locations/" + l->name);
		return true;
	}
	
	std::cout << "---\nERROR: invalid element index\n---\n" << std::endl;
	return false;
}

bool addCharacter(int index)
{
	if (index == -1)
	{
		const Character& c = File::Get().characters.emplace_back();
		std::filesystem::create_directories(File::Get().path + "/characters/" + c.name);
		return true;
	}
	if (index < File::Get().characters.size())
	{
		const auto& c = File::Get().characters.emplace(File::Get().characters.begin() + index);
		std::filesystem::create_directories(File::Get().path + "/characters/" + c->name);
		return true;
	}
	
	std::cout << "---\nERROR: invalid element index\n---\n" << std::endl;
	return false;
}


bool delSession(int index)
{
	const auto& s = File::Get().sessions;

	if (index == -1)
	{
		std::filesystem::remove(File::Get().path + "/sessions/" + s[s.size() - 1].name);
		File::Get().sessions.pop_back();
		return true;
	}
	if (index < File::Get().sessions.size())
	{
		std::filesystem::remove(File::Get().path + "/sessions/" + s[index].name);
		File::Get().sessions.erase(File::Get().sessions.begin() + index);
		return true;
	}

	std::cout << "---\nERROR: invalid element index\n---\n" << std::endl;
	return false;
}

bool delLocation(int index)
{
	const auto& l = File::Get().locations;

	if (index == -1)
	{
		std::filesystem::remove(File::Get().path + "/locations/" + l[l.size() - 1].name);
		File::Get().locations.pop_back();
		return true;
	}
	if (index < File::Get().locations.size())
	{
		std::filesystem::remove(File::Get().path + "/locations/" + l[index].name);
		File::Get().locations.erase(File::Get().locations.begin() + index);
		return true;
	}

	std::cout << "---\nERROR: invalid element index\n---\n" << std::endl;
	return false;
}

bool delCharacter(int index)
{
	const auto& c = File::Get().characters;

	if (index == -1)
	{
		std::filesystem::remove(File::Get().path + "/characters/" + c[c.size() - 1].name);
		File::Get().characters.pop_back();
		return true;
	}
	if (index < File::Get().characters.size())
	{
		std::filesystem::remove(File::Get().path + "/characters/" + c[index].name);
		File::Get().characters.erase(File::Get().characters.begin() + index);
		return true;
	}

	std::cout << "---\nERROR: invalid element index\n---\n" << std::endl;
	return false;
}


bool addSessionComp(uint32_t fIndex, int iIndex)
{
	if (fIndex >= File::Get().sessions.size())
	{
		std::cout << "---\nERROR: invalid element index\n---\n" << std::endl;
		return false;
	}

	Session& s = File::Get().sessions[fIndex];
	std::string filePath;

	if (iIndex == -1)
	{
		s.elems.emplace_back("New Element" + std::to_string(s.elems.size()));
		filePath = File::Get().path + "/sessions/" + s.name + "/" + s.elems[s.elems.size() - 1] + ".txt";
		std::ofstream stream(filePath);
		return true;
	}
	if (iIndex < s.elems.size())
	{
		s.elems.emplace(s.elems.begin() + iIndex, "New Element" + std::to_string(s.elems.size()));
		filePath = File::Get().path + "/sessions/" + s.name + "/" + s.elems[iIndex] + ".txt";
		std::ofstream stream(filePath);
		return true;
	}

	std::cout << "---\nERROR: invalid article index\n---\n" << std::endl;
	return false;
}

bool addLocationComp(uint32_t fIndex, int iIndex)
{
	if (fIndex >= File::Get().locations.size())
	{
		std::cout << "---\nERROR: invalid element index\n---\n" << std::endl;
		return false;
	}

	Location& l = File::Get().locations[fIndex];
	std::string filePath;

	if (iIndex == -1)
	{
		l.prehistory.emplace_back("New Location" + std::to_string(l.prehistory.size()));
		filePath = File::Get().path + "/locations/" + l.name + "/" + l.prehistory[l.prehistory.size() - 1] + ".txt";
		std::ofstream stream(filePath);
		return true;
	}
	if (iIndex < l.prehistory.size())
	{
		l.prehistory.emplace(l.prehistory.begin() + iIndex, "New Location" + std::to_string(l.prehistory.size()));
		filePath = File::Get().path + "/locations/" + l.name + "/" + l.prehistory[iIndex] + ".txt";
		std::ofstream stream(filePath);
		return true;
	}

	std::cout << "---\nERROR: invalid article index\n---\n" << std::endl;
	return false;
}

bool addCharacterComp(uint32_t fIndex, int iIndex)
{
	if (fIndex >= File::Get().characters.size())
	{
		std::cout << "---\nERROR: invalid element index\n---\n" << std::endl;
		return false;
	}

	Character& c = File::Get().characters[fIndex];
	std::string filePath;

	if (iIndex == -1)
	{
		c.backstory.emplace_back("New Chapter" + std::to_string(c.backstory.size()));
		filePath = File::Get().path + "/characters/" + c.name + "/" + c.backstory[c.backstory.size() - 1] + ".txt";
		std::ofstream stream(filePath);
		return true;
	}
	else
	{
		c.backstory.emplace(c.backstory.begin() + iIndex, "New Chapter" + std::to_string(c.backstory.size()));
		filePath = File::Get().path + "/characters/" + c.name + "/" + c.backstory[iIndex] + ".txt";
		std::ofstream stream(filePath);
		return true;
	}

	std::cout << "---\nERROR: invalid article index\n---\n" << std::endl;
	return false;
}


bool delSessionComp(uint32_t fIndex, int iIndex)
{
	if (fIndex >= File::Get().sessions.size())
	{
		std::cout << "---\nERROR: invalid element index\n---\n" << std::endl;
		return false;
	}

	Session& s = File::Get().sessions[fIndex];
	std::string filePath;

	if (iIndex == -1)
	{
		filePath = File::Get().path + "/sessions/" + s.name + "/" + s.elems[s.elems.size() - 1] + ".txt";
		s.elems.pop_back();
		std::remove(filePath.c_str());
		return true;
	}
	if (iIndex < s.elems.size())
	{
		filePath = File::Get().path + "/sessions/" + s.name + "/" + s.elems[iIndex] + ".txt";
		s.elems.erase(s.elems.begin() + iIndex);
		std::remove(filePath.c_str());
		return true;
	}

	std::cout << "---\nERROR: invalid article index\n---\n" << std::endl;
	return false;
}

bool delLocationComp(uint32_t fIndex, int iIndex)
{
	if (fIndex >= File::Get().locations.size())
	{
		std::cout << "---\nERROR: invalid element index\n---\n" << std::endl;
		return false;
	}

	Location& l = File::Get().locations[fIndex];
	std::string filePath;

	if (iIndex == -1)
	{
		filePath = File::Get().path + "/locations/" + l.name + "/" + l.prehistory[l.prehistory.size() - 1] + ".txt";
		l.prehistory.pop_back();
		std::remove(filePath.c_str());
		return true;
	}
	if (iIndex < l.prehistory.size())
	{
		filePath = File::Get().path + "/locations/" + l.name + "/" + l.prehistory[iIndex] + ".txt";
		l.prehistory.erase(l.prehistory.begin() + iIndex);
		std::remove(filePath.c_str());
		return true;
	}

	std::cout << "---\nERROR: invalid article index\n---\n" << std::endl;
	return false;
}

bool delCharacterComp(uint32_t fIndex, int iIndex)
{
	if (fIndex >= File::Get().characters.size())
	{
		std::cout << "---\nERROR: invalid element index\n---\n" << std::endl;
		return false;
	}

	Character& c = File::Get().characters[fIndex];
	std::string filePath;

	if (iIndex == -1)
	{
		filePath = File::Get().path + "/characters/" + c.name + "/" + c.backstory[c.backstory.size() - 1] + ".txt";
		c.backstory.pop_back();
		std::remove(filePath.c_str());
		return true;
	}
	if (iIndex < c.backstory.size())
	{
		filePath = File::Get().path + "/characters/" + c.name + "/" + c.backstory[iIndex] + ".txt";
		c.backstory.erase(c.backstory.begin() + iIndex);
		std::remove(filePath.c_str());
		return true;
	}

	std::cout << "---\nERROR: invalid article index\n---\n" << std::endl;
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

	switch (loc.folderIndex)
	{
	case 0:
		if (loc.componentIndex != -2)
		{
			if (!addSessionComp(loc.elementIndex, loc.componentIndex))
				return false;
		}
		else if (!addSession(loc.elementIndex))
			return false;
		break;
	case 1:
		if (loc.componentIndex != -2)
		{
			if (!addLocationComp(loc.elementIndex, loc.componentIndex))
				return false;
		}
		else if (!addLocation(loc.elementIndex))
			return false;
		break;
	case 2:
		if (loc.componentIndex != -2)
		{
			if (!addCharacterComp(loc.elementIndex, loc.componentIndex))
				return false;
		}
		else if (!addCharacter(loc.elementIndex))
			return false;
		break;
	}

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

	switch (loc.folderIndex)
	{
	case 0:
		if (loc.componentIndex != -2)
		{
			if (!delSessionComp(loc.elementIndex, loc.componentIndex))
				return false;
		}
		else if (!delSession(loc.elementIndex))
			return false;
		break;
	case 1:
		if (loc.componentIndex != -2)
		{
			if (!delLocationComp(loc.elementIndex, loc.componentIndex))
				return false;
		}
		else if (!delLocation(loc.elementIndex))
			return false;
		break;
	case 2:
		if (loc.componentIndex != -2)
		{
			if (!delCharacterComp(loc.elementIndex, loc.componentIndex))
				return false;
		}
		else if (!delCharacter(loc.elementIndex))
			return false;
		break;
	}

	listElements((ARG)command[1]);

	return true;
}