#pragma once

#include "Session.h"
#include "Location.h"
#include "Character.h"


class File
{
private:
	File() {}

	struct VirtualFileSystem
	{
		int folderIndex = -1;
		int itemIndex = -1;
	};


public:
	std::string dir;
	std::string path;
	std::string name;

	VirtualFileSystem vfs;

	std::vector<Session> sessions;
	std::vector<Location> locations;
	std::vector<Character> characters;


	void save(const std::string& path);
	void load(const std::string& path);
	void reset();


    static File& Get()
    {
        static File instance;
        return instance;
    }
	~File() { save(path); }

	File(const File&) = delete;
	void operator=(const File&) = delete;
};