#include "PCH.h"
#include "FileManagement.h"

#include "core/Exceptions.h"
#include "core/Macros.h"
#include "files/File.h"

#include "Files/Dialogs.h"


void cmdCreate()
{
	const fs::path rootdir = saveFileName("");

	fs::create_directories(rootdir / "sessions");
	fs::create_directories(rootdir / "locations");
	fs::create_directories(rootdir / "characters");
	fs::create_directories(rootdir / "items");

	const fs::path filepath = rootdir / "camp.ft";
	std::ofstream stream(filepath);
	if (!stream.is_open())
		throw FileNotFound("unable to create file at specified location");
	stream << "{\"sessions\":[],\"locations\":[],\"characters\":[],\"items\":[]}";
	stream.close();

	File::Get().reset();
	File::Get().rootdir = rootdir;
	File::Get().filepath = filepath;

	std::ifstream istream("res/startup.json");
	if (!istream.is_open())
		throw FileNotFound("unable to open startup file");

	nlohmann::json j;
	istream >> j;
	istream.close();
	j["lastfile"] = filepath;

	std::ofstream ostream("res/startup.json");
	if (!ostream.is_open())
		throw FileNotFound("unable to open startup file");

	ostream << j;
	ostream.close();
}

void cmdOpen()
{
	const fs::path filepath = openFileName("tome files (*.ft)\0*.ft\0");

	File::Get().reset();
	File::Get().load(filepath);
	{
		//LOG_ERROR("failed to open file at specified location");
		//return false;
	}

	std::ifstream istream("res/startup.json");
	if (!istream.is_open())
		throw FileNotFound("unable to open startup file");

	nlohmann::json j;
	istream >> j;
	istream.close();
	j["lastfile"] = filepath;

	std::ofstream ostream("res/startup.json");
	if (!ostream.is_open())
		throw FileNotFound("unable to open startup file");

	ostream << j;
	ostream.close();
}

void cmdSave()
{
	File::Get().save(File::Get().filepath);
}

void cmdClose()
{
	File::Get().reset();

	std::ifstream istream("res/startup.json");
	if (!istream.is_open())
		throw FileNotFound("unable to open startup file");

	nlohmann::json j;
	istream >> j;
	istream.close();
	j["lastfile"] = "empty";
	j["selected"] = nullptr;

	std::ofstream ostream("res/startup.json");
	if (!ostream.is_open())
		throw FileNotFound("unable to open startup file");

	ostream << j;
	ostream.close();
}