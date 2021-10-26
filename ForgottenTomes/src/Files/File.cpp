#include "PCH.h"
#include "File.h"

#include "CoreMacros.h"
#include "CMDenums.h"


void File::save(const std::string& filepath)
{
	this->filepath = filepath;

	std::ofstream stream(filepath, std::ofstream::trunc);
	if (stream.is_open())
	{
		nlohmann::json j;
		
		j["sessions"] = nlohmann::json::array();
		for (size_t i = 0; i < elements[0].size(); i++)
			j["sessions"].push_back(elements[0][i].serialize());

		j["locations"] = nlohmann::json::array();
		for (size_t i = 0; i < elements[1].size(); i++)
			j["locations"].push_back(elements[1][i].serialize());

		j["characters"] = nlohmann::json::array();
		for (size_t i = 0; i < elements[2].size(); i++)
			j["characters"].push_back(elements[2][i].serialize());

		j["items"] = nlohmann::json::array();
		for (size_t i = 0; i < elements[3].size(); i++)
			j["items"].push_back(elements[3][i].serialize());

		stream << j;
		stream.close();

		rootdir = filepath.substr(0, filepath.rfind('/'));
	}
}

bool File::load(const std::string& filepath)
{
	this->filepath = filepath;

	std::ifstream stream(filepath);
	if (stream.is_open())
	{
		nlohmann::json j;
		stream >> j;

		for (const auto& s : j["sessions"])
			elements[0].emplace_back(0, s);

		for (const auto& l : j["locations"])
			elements[1].emplace_back(1, l);

		for (const auto& c : j["characters"])
			elements[2].emplace_back(2, c);

		for (const auto& i : j["items"])
			elements[3].emplace_back(3, i);

		stream.close();

		rootdir = filepath.substr(0, filepath.rfind('/'));

		return true;
	}
	else
		return false;
}

void File::reset()
{
	rootdir.clear();
	filepath.clear();

	for (size_t i = 0; i < 4; i++)
		elements[i].clear();
}


File& File::Get()
{
	static File instance;
	return instance;
}


bool File::IsSelected()
{
	if (Get().selected.category == 4 || Get().selected.element == -1)
		return false;

	return true;
}

std::optional<ItemLocation> File::Selected()
{
	if (!IsSelected())
	{
		LOG_ERROR("no item selected");
		return {};
	}

	return Get().selected;
}


std::vector<Element>& File::Category(uint32_t category)
{
	return Get().elements[category];
}

Element& File::Element(ItemLocation loc)
{
	return Get().elements[loc.category][loc.element];
}

const std::string& File::Article(ItemLocation loc)
{
	return Get().elements[loc.category][loc.element].content[loc.article];
}