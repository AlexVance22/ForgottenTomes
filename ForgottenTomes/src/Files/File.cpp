#include "PCH.h"

#include "File.h"


void File::save(const std::string& path)
{
	dir = path;

	std::ofstream f(path, std::ofstream::out | std::ofstream::trunc);
	if (f.is_open())
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

		f << j;
		f.close();

		this->path = path.substr(0, path.rfind('\\'));
	}
}

bool File::load(const std::string& path)
{
	dir = path;

	std::ifstream f(path, std::ifstream::in);
	if (f.is_open())
	{
		nlohmann::json j;
		f >> j;

		for (const auto& s : j["sessions"])
			elements[0].emplace_back(s);

		for (const auto& l : j["locations"])
			elements[1].emplace_back(l);

		for (const auto& c : j["characters"])
			elements[2].emplace_back(c);

		for (const auto& c : j["items"])
			elements[3].emplace_back(c);

		f.close();

		this->path = path.substr(0, path.rfind('\\'));

		return true;
	}
	else
		return false;
}

void File::reset()
{
	dir.clear();
	path.clear();
	name.clear();

	for (size_t i = 0; i < 4; i++)
		elements[i].clear();
}