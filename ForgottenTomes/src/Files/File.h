#pragma once

#include "CampaignElem.h"


struct ItemLocation
{
	int folderIndex = -1;
	int elementIndex = -1;
	int componentIndex = -2;
};


class File
{
private:
	File() {}


public:
	std::string dir;
	std::string path;
	std::string name;

	ItemLocation selected;

	std::vector<Element> elements[4];


	void save(const std::string& path);
	bool load(const std::string& path);
	void reset();


    static File& Get()
    {
        static File instance;
        return instance;
    }
	static ItemLocation& Selected() { return Get().selected; }
	~File() { save(path); }

	File(const File&) = delete;
	void operator=(const File&) = delete;
};