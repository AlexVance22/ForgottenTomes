#include "PCH.h"

#include "Utilities.h"

#include "File.h"
#include "CMDenums.h"
#include "Helpers.h"


bool listElement()
{
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


void viewSession(size_t iIndex)
{
	const auto& ses = File::Get().sessions[iIndex];

	std::cout << "Name: " << ses.name << "\n\n";
	std::cout << "Content:\n\n";

	for (size_t i = 0; i < ses.elems.size(); i++)
	{
		std::cout << "-" << ses.elems[i] << ":" << "\n\n";
		printFile(File::Get().path + "/sessions/" + ses.name + "/" + ses.elems[i] + ".txt");

		std::cout << std::endl;
	}
}

void viewLocation(size_t iIndex)
{
	const auto& loc = File::Get().locations[iIndex];

	std::cout << "Name: " << loc.name << "\n\n";
	std::cout << "Content:\n\n";

	for (size_t i = 0; i < loc.prehistory.size(); i++)
	{
		std::cout << "-" << loc.prehistory[i] << ":" << "\n\n";
		printFile(File::Get().path + "/locations/" + loc.name + "/" + loc.prehistory[i] + ".txt");

		std::cout << std::endl;
	}

	for (size_t i = 0; i < loc.posthistory.size(); i++)
	{
		std::cout << "-" << loc.posthistory[i] << ":" << "\n\n";
		printFile(File::Get().path + "/locations/" + loc.name + "/" + loc.posthistory[i] + ".txt");

		std::cout << std::endl;
	}
}

void viewCharacter(size_t iIndex)
{
	const auto& cha = File::Get().characters[iIndex];

	std::cout << "Name: " << cha.name << "\n\n";
	std::cout << "Content:\n\n";

	for (size_t i = 0; i < cha.backstory.size(); i++)
	{
		std::cout << "-" << cha.backstory[i] << ":" << "\n\n";
		printFile(File::Get().path + "/characters/" + cha.name + "/" + cha.backstory[i] + ".txt");

		std::cout << std::endl;
	}
}


void viewSessionComp(size_t iIndex, size_t cIndex)
{
	const auto& ses = File::Get().sessions[iIndex];

	std::cout << "Session: " << ses.name << "\n\n";
	std::cout << "Index: " << cIndex << "\n\n";

	std::cout << ses.elems[cIndex] << "\n\n";
	printFile(File::Get().path + "/sessions/" + ses.name + "/" + ses.elems[cIndex] + ".txt");
}

void viewLocationComp(size_t iIndex, size_t cIndex)
{
	const auto& loc = File::Get().locations[iIndex];

	std::cout << "Location: " << loc.name << "\n\n";
	std::cout << "Index: " << cIndex << "\n\n";

	std::cout << loc.prehistory[cIndex] << "\n\n";
	printFile(File::Get().path + "/locations/" + loc.name + "/" + loc.prehistory[cIndex] + ".txt");

	/*
	for (size_t i = 0; i < loc.posthistory.size(); i++)
	{
		std::cout << loc.posthistory[i] << "\n\n";
		printFile(File::Get().path + "/locations/" + loc.name + "/" + loc.posthistory[i] + ".txt");
	}
	*/
}

void viewCharacterComp(size_t iIndex, size_t cIndex)
{
	const auto& cha = File::Get().characters[iIndex];

	std::cout << "Character: " << cha.name << "\n\n";
	std::cout << "Index: " << cIndex << "\n\n";

	std::cout << cha.backstory[cIndex] << "\n\n";
	printFile(File::Get().path + "/characters/" + cha.name + "/" + cha.backstory[cIndex] + ".txt");
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
	int group = 0;

	switch ((ARG)command[1])
	{
	case ARG::SES:
		group = 0;
		break;
	case ARG::LOC:
		group = 1;
		break;
	case ARG::CHA:
		group = 2;
		break;
	default:
		std::cout << "---\nERROR: invalid element type\n---" << std::endl;
		return false;
	}

	File::Get().vfs.folderIndex = group;
	File::Get().vfs.itemIndex = command[2];

	cmdView({ 0, (int)ARG::CRN, 1 });

	return true;
}

bool cmdView(const std::vector<int>& command)
{
	ItemLocation loc;
	if (!findItem(loc, command, 1))
		return false;

	switch (loc.folderIndex)
	{
	case 0:
		if (loc.componentIndex != -2)
			viewSessionComp(loc.elementIndex, loc.componentIndex);
		else
			viewSession(loc.elementIndex);
		break;
	case 1:
		if (loc.componentIndex != -2)
			viewLocationComp(loc.elementIndex, loc.componentIndex);
		else
			viewLocation(loc.elementIndex);
		break;
	case 2:
		if (loc.componentIndex != -2)
			viewCharacterComp(loc.elementIndex, loc.componentIndex);
		else
			viewCharacter(loc.elementIndex);
		break;
	}

	std::cout << "-------------------------------------------\n" << std::endl;

	return true;
}