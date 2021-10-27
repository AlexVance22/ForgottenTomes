#include "PCH.h"
#include "FileManagement.h"

#include "CoreMacros.h"
#include "Files/File.h"

#include "Files/Dialogs.h"


bool cmdCreate()
{
	std::string rootdir = saveFileName("");
	std::replace(rootdir.begin(), rootdir.end(), '\\', '/');

	std::filesystem::create_directories(rootdir);

	std::filesystem::create_directories(rootdir + "/sessions");
	std::filesystem::create_directories(rootdir + "/locations");
	std::filesystem::create_directories(rootdir + "/characters");
	std::filesystem::create_directories(rootdir + "/items");

	std::ofstream stream(rootdir + "/camp.ft");
	if (!stream.is_open())
	{
		LOG_ERROR("failed to create file at specified location");
		return false;
	}
	stream << "{\"sessions\":[],\"locations\":[],\"characters\":[],\"items\":[]}";
	stream.close();

	File::Get().reset();
	File::Get().rootdir = rootdir;
	File::Get().filepath = rootdir + "/camp.ft";

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
	return true;
}

void cmdSave()
{
	File::Get().save(File::Get().filepath);
}