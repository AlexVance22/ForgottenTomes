#pragma once

#include "CampaignElem.h"


struct Location : public CampaignElem
{
	static uint32_t count;

	enum class Size { Invalid = -1, Building, Village, Town, City, Metropolis, Province, State, Union, Continent };
	Size size = Size::Invalid;

	std::vector<std::string> prehistory;
	std::vector<std::string> posthistory;


	Location() : CampaignElem(count++) { name = "Location"; }
	Location(const nlohmann::json& data) : CampaignElem(0) { deserialize(data); }

	nlohmann::json serialize() const;
	void deserialize(const nlohmann::json& data);
};