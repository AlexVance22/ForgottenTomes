#pragma once

#include "CampaignElem.h"


enum class ARG;


struct ItemLocation
{
	size_t category = 4;
	int element = -1;
	int article = -1;
};


class File
{
private:
	File() {}

public:
	std::string rootdir;
	std::string filepath;

	ItemLocation selected;

	std::vector<Element> elements[4];

	void save(const std::string& filepath);
	bool load(const std::string& filepath);
	void reset();

	static File& Get();

	static bool IsSelected();
	static std::optional<ItemLocation> Selected();

	static std::vector<Element>& Category(uint32_t category);
	static Element& Element(ItemLocation loc);
	static const std::string& Article(ItemLocation loc);

	File(const File&) = delete;
	void operator=(const File&) = delete;
};