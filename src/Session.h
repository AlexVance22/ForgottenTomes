#pragma once

#include "CampaignElem.h"


struct Session : public CampaignElem
{
	static uint32_t count;

	std::vector<std::string> elems;


	Session() : CampaignElem(count++) { name = "Session" + std::to_string(number); }
	Session(const nlohmann::json& data) : CampaignElem(0) { deserialize(data); }

	nlohmann::json serialize() const;
	void deserialize(const nlohmann::json& data);
};