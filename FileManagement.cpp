#include "PCH.h"

#include "FileManagement.h"

#include "File.h"
#include "Dialogs.h"


void cmdOpen()
{
	std::string dir = openFileName("tome files (*.ft)\0*.ft\0", GetConsoleWindow());

	File::Get().reset();
	File::Get().load(dir);
}

void cmdSave()
{
	File::Get().save(File::Get().dir);
}

void cmdCreate()
{
	std::string dir = saveFileName("", GetConsoleWindow());

	std::filesystem::create_directories(dir);

	std::filesystem::create_directories(dir + "/sessions");
	std::filesystem::create_directories(dir + "/locations");
	std::filesystem::create_directories(dir + "/characters");

	std::ofstream stream(dir + "/camp.ft");
	stream << "{\"sessions\":[],\"locations\":[],\"characters\":[]}";
	stream.close();

	File::Get().reset();
	File::Get().dir = dir + "\\camp.ft";
	File::Get().path = dir;
}