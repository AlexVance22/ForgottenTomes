#include "PCH.h"

#include "FileManagement.h"

#include "Files/File.h"
#include "Files/Dialogs.h"


void save()
{
	File::Get().save(File::Get().dir);
}


bool cmdCreate()
{
	std::string dir = saveFileName("");

	std::filesystem::create_directories(dir);

	std::filesystem::create_directories(dir + "/sessions");
	std::filesystem::create_directories(dir + "/locations");
	std::filesystem::create_directories(dir + "/characters");
	std::filesystem::create_directories(dir + "/items");

	std::ofstream stream(dir + "/camp.ft");
	if (!stream.is_open())
	{
		std::cout << "---\nERROR: failed to create file at specified location\n---\n";
		return false;
	}
	stream << "{\"sessions\":[],\"locations\":[],\"characters\":[],\"items\":[]}";
	stream.close();

	File::Get().reset();
	File::Get().dir = dir + "\\camp.ft";
	File::Get().path = dir;

	return true;
}

bool cmdOpen()
{
	std::string dir = openFileName("tome files (*.ft)\0*.ft\0");

	File::Get().reset();
	if (!File::Get().load(dir))
	{
		std::cout << "---\nERROR: failed to open file at specified location\n---\n";
		return false;
	}
	return true;
}

void cmdSave(std::vector<std::future<void>>& futures)
{
	futures.push_back(std::async(std::launch::async, save));
}