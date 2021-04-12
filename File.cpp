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
		for (size_t i = 0; i < sessions.size(); i++)
			j["sessions"].push_back(sessions[i].serialize());

		j["locations"] = nlohmann::json::array();
		for (size_t i = 0; i < locations.size(); i++)
			j["locations"].push_back(locations[i].serialize());

		j["characters"] = nlohmann::json::array();
		for (size_t i = 0; i < characters.size(); i++)
			j["characters"].push_back(characters[i].serialize());

		f << j;
		f.close();

		this->path = path.substr(0, path.rfind('\\'));
	}
}

void File::load(const std::string& path)
{
	dir = path;

	std::ifstream f(path, std::ifstream::in);
	if (f.is_open())
	{
		nlohmann::json j;
		f >> j;

		for (const auto& s : j["sessions"])
			sessions.emplace_back(s);

		for (const auto& l : j["locations"])
			locations.emplace_back(l);

		for (const auto& c : j["characters"])
			characters.emplace_back(c);

		f.close();

		this->path = path.substr(0, path.rfind('\\'));
	}
	else if (path == "")
		name = "invalid";

}

void File::reset()
{
	dir.clear();
	path.clear();
	name.clear();

	sessions.clear();
	locations.clear();
	characters.clear();
}