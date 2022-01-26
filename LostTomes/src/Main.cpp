#include "PCH.h"

#include "core/Exceptions.h"
#include "core/Macros.h"
#include "files/File.h"

#include "commands/FileManagement.h"
#include "commands/ElementStorage.h"
#include "commands/References.h"
#include "commands/Utilities.h"
#include "commands/Editing.h"
#include "commands/Help.h"

#include "Parsing.h"


//bug: system function ignoring if condition
void cmdClear(const std::vector<Argument>& command, bool& cls)
{
	if (command.size() == 1)
	{
		system("CLS");
		return;
	}

	if (command[1].type != Argument::Type::Bool && command[1].type != Argument::Type::Index)
		throw InvalidArgument("invalid boolean value");

	cls = (bool)command[1].numerical;
	if (cls)
		system("CLS");

	std::ifstream istream("res/startup.json");
	if (!istream.is_open())
		throw FileNotFound("unable to open startup file");

	nlohmann::json j;
	istream >> j;
	istream.close();
	j["clearscreen"] = cls;

	std::ofstream ostream("res/startup.json");
	if (!ostream.is_open())
		throw FileNotFound("unable to open startup file");

	ostream << j;
	ostream.close();
}


bool startup()
{
	std::ifstream stream("res/startup.json");
	if (!stream.is_open())
		throw FileNotFound("cannot open startup file");

	nlohmann::json j;
	stream >> j;
	stream.close();

	const bool cls = j["clearscreen"];

	if (!j["selected"].is_null())
	{
		File::Get().selected.category = j["selected"]["category"];
		File::Get().selected.element = j["selected"]["element"];
	}

	if (j["lastfile"] == "empty")
		throw FileNotFound("no file open");

	File::Get().load(fs::path((std::string)j["lastfile"]));

	std::cout << "Reopened last workspace\n";

	return cls;
}


void fileNotOpen(const std::vector<Argument>& command, bool& cls)
{
	switch (command[0].numerical)
	{
	case "cls"_hash:
		cmdClear(command, cls);
		break;
	case "hlp"_hash:
		cmdHelp(command);
		break;
	case "new"_hash:
		cmdCreate();
		break;
	case "opn"_hash:
		cmdOpen();
		break;
	default:
		throw FileNotFound("no file is open");
	}
	/*
		if (!open)
		{
			LOG_ERROR("no file open");
			continue;
		}
	*/
}

void fileOpen(const std::vector<Argument>& command, bool& cls)
{
	switch (command[0].numerical)
	{
	case "dir"_hash:
		std::cout << File::Get().rootdir << '\n';
		break;
	case "cls"_hash:
		cmdClear(command, cls);
		break;
	case "hlp"_hash:
		cmdHelp(command);
		break;
	case "lst"_hash:
		cmdList(command);
		break;
	case "slt"_hash:
		cmdSelect(command);
		break;
	case "vew"_hash:
		cmdView(command);
		break;
	case "lkp"_hash:
		cmdLookup(command);
		break;
	case "add"_hash:
		cmdAdd(command);
		break;
	case "del"_hash:
		cmdDel(command);
		break;
	case "edt"_hash:
		cmdEdit(command);
		break;
	case "rnm"_hash:
		cmdRename(command);
		break;
	case "new"_hash:
		cmdCreate();
		break;
	case "opn"_hash:
		cmdOpen();
		break;
	case "close"_hash:
		cmdClose();
		break;
	default:
		throw InvalidArgument("unrecognised command");
	}
}


int main()
{
	std::cout << C_RESET;
	system("CLS");
	bool open = true;
	bool cls = true;
	
	try
	{
		cls = startup();
	}
	catch (const FileNotFound& e)
	{
		open = false;
		cls = false;

		if (!e.silent)
			LOG_ERROR(e.what());
	}

	while (true)
	{
		const std::vector<Argument> command = getCommand();
		if (command.size() == 0)
			continue;

		if (cls)
			system("CLS");

		try
		{
			if (open)
				fileOpen(command, cls);
			else
				fileNotOpen(command, cls);
		}
		catch (const std::exception& e)
		{
			LOG_ERROR(e.what());
		}

		std::cout.flush();
	}
}