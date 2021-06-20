#include "PCH.h"
#include "References.h"

#include "CoreMacros.h"

#include "Files/File.h"
#include "Helpers.h"
#include "Utilities.h"
#include "Files/CampaignElem.h"


static std::vector<std::string> collectRefNames(const std::string& file)
{
	std::ifstream stream(file);
	if (!stream.is_open())
	{
		std::cout << "failed to open" << std::endl;
		return {};
	}

	std::vector<std::string> refs;

	std::string token;
	while (stream >> token)
	{
		if (token[0] == '[')
		{
			std::string ref;

			for (bool foundEnd = false; !foundEnd;)
			{
				size_t index = token.find(']');
				if (index != std::string::npos)
				{
					ref += token.substr(0, index + 1);
					refs.push_back(ref);
					foundEnd = true;
				}
				else
					ref += token + ' ';

				if (!foundEnd && !(stream >> token))
				{
					std::cout << "---\nERROR: end of reference token \']\' not found\n---" << std::endl;
					return {};
				}
			}
		}
	}

	stream.close();

	return refs;
}

static std::vector<std::pair<std::string, ItemLocation>> findRefs(const std::vector<std::string>& tokens)
{
	std::vector<std::pair<std::string, ItemLocation>> result;

	for (int i = 0; i < 4; i++)
	{
		const auto& es = File::Get().elements[i];

		for (const auto& t : tokens)
		{
			auto it = std::find_if(es.begin(), es.end(), [&](const Element& e) { return "[" + e.name + "]" == t; });

			if (it != es.end())
			{
				ItemLocation loc;
				loc.folderIndex = i;
				loc.elementIndex = it - es.begin();
				result.push_back({ t, loc });
			}
		}
	}

	return result;
}


bool cmdLookup(const std::vector<int>& command)
{
	ItemLocation loc;
	if (!findItem(loc, command, 1))
		return false;

	std::string path = File::Get().path;

	switch (loc.folderIndex)
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

	path += File::Get().elements[loc.folderIndex][loc.elementIndex].name + '\\' + File::Get().elements[loc.folderIndex][loc.elementIndex].content[loc.componentIndex];

	std::vector<std::string> refTokens = collectRefNames(path + ".txt");

	std::vector<std::pair<std::string, ItemLocation>> refLocs = findRefs(refTokens);

	printFile(path + ".txt");
	std::cout << '\n';

	for (size_t i = 0; i < refTokens.size(); i++)
	{
		auto it = std::find_if(refLocs.begin(), refLocs.end(), [&](const std::pair<std::string, ItemLocation>& pair) { return pair.first == refTokens[i]; });

		if (it != refLocs.end())
			std::cout << i << ": " << it->first << '\n';
		else
			std::cout << i << ": " << refTokens[i] << C_YELLOW << " -> unimplemented element\n" << C_RESET;
	}

	std::cout << "\nEnter 'exit' to cancel\n";

	while (true)
	{
		std::cout << "\nSelect and go to: ";

		std::string index;
		std::cin.ignore(0);
		std::getline(std::cin, index);
		if (strHash(index) == -840099195) return true;
		int i = stoi(index);

		auto it = std::find_if(refLocs.begin(), refLocs.end(), [&](const std::pair<std::string, ItemLocation>& pair) { return pair.first == refTokens[i]; });

		if (it != refLocs.end())
		{
			std::cout << '\n';
			File::Selected() = it->second;
			cmdView({ (int)CMD::VEW, (int)ARG::CRN });
			return true;
		}
		else
			std::cout << "Element is not implemented\n\n";
	}
	
	return true;
}