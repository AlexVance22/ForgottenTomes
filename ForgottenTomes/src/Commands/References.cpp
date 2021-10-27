#include "PCH.h"
#include "References.h"

#include "core/Macros.h"
#include "files/File.h"

#include "Helpers.h"
#include "Parsing.h"

#include "Utilities.h"


static std::vector<std::string> collectRefNames(const std::string& filepath)
{
	std::ifstream stream(filepath);
	if (!stream.is_open())
	{
		LOG_ERROR("failed to open file");
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
				loc.category = i;
				loc.element = it - es.begin();
				result.push_back({ t, loc });
			}
		}
	}

	return result;
}


bool cmdLookup(const std::vector<Argument>& command)
{
	ItemLocation loc;
	if (!parseLocStr(loc, command, 1))
		return false;

	std::string path = categoryPath(loc.category);
	path += File::Element(loc).name + '/' + File::Article(loc);

	std::vector<std::string> refTokens = collectRefNames(path + ".txt");
	std::vector<std::pair<std::string, ItemLocation>> refLocs = findRefs(refTokens);

	std::cout << C_CYAN;
	printFile(path + ".txt");
	std::cout << C_RESET << '\n';

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
		if (index == "exit")
		{
			std::cout << '\n';
			return true;
		}
		int i = stoi(index);

		auto it = std::find_if(refLocs.begin(), refLocs.end(), [&](const std::pair<std::string, ItemLocation>& pair) { return pair.first == refTokens[i]; });

		if (it != refLocs.end())
		{
			std::cout << '\n';
			File::Get().selected = it->second;
			system("CLS");
			std::cout << C_CYAN;
			ItemLocation sel = it->second;
			viewElement(sel.category, sel.element);
			std::cout << "\n-------------------------------------------\n\n" << C_RESET;
			return true;
		}
		else
			std::cout << C_RED << "\nElement is not implemented\n\n" << C_RESET;
	}
	
	return true;
}