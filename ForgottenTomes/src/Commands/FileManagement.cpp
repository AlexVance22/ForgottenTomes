#include "PCH.h"
#include "FileManagement.h"

#include "core/Macros.h"
#include "files/File.h"

#include "Files/Dialogs.h"


static bool JsonFileChangeStr(const std::string& filepath, const std::string& key, const std::string& val)
{
	std::ifstream istream("res/startup.json");
	if (istream.is_open())
	{
		nlohmann::json j;
		istream >> j;
		istream.close();
		j[key] = val;

		std::ofstream ostream("res/startup.json", std::ios::trunc);
		if (ostream.is_open())
		{
			ostream << j;
			ostream.close();
			return true;
		}
	}
	return false;
}


bool cmdCreate()
{
	std::string rootdir = saveFileName("");
	std::replace(rootdir.begin(), rootdir.end(), '\\', '/');

	std::filesystem::create_directories(rootdir);
	std::filesystem::create_directories(rootdir + "/sessions");
	std::filesystem::create_directories(rootdir + "/locations");
	std::filesystem::create_directories(rootdir + "/characters");
	std::filesystem::create_directories(rootdir + "/items");

	std::string filepath = rootdir + "/camp.ft";
	std::ofstream stream(filepath);
	stream << "{\"sessions\":[],\"locations\":[],\"characters\":[],\"items\":[]}";
	stream.close();

	File::Get().reset();
	File::Get().rootdir = rootdir;
	File::Get().filepath = filepath;

	if (!JsonFileChangeStr("res/startup.json", "lastfile", filepath))
	{
		LOG_ERROR("startup file missing");
		return false;
	}

	return true;
}

bool cmdOpen()
{
	std::string filepath = openFileName("tome files (*.ft)\0*.ft\0");
	std::replace(filepath.begin(), filepath.end(), '\\', '/');

	File::Get().reset();
	if (!File::Get().load(filepath))
	{
		LOG_ERROR("failed to open file at specified location");
		return false;
	}

	if (!JsonFileChangeStr("res/startup.json", "lastfile", filepath))
	{
		LOG_ERROR("startup file missing");
		return false;
	}

	return true;
}

void cmdSave()
{
	File::Get().save(File::Get().filepath);
}

void cmdClose()
{
	File::Get().reset();

	if (!JsonFileChangeStr("res/startup.json", "lastfile", "empty"))
	{
		LOG_ERROR("startup file missing");
		return;
	}
}