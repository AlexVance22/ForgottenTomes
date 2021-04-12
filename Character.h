#pragma once

#include "CampaignElem.h"


struct Character : public CampaignElem
{
	static uint32_t count;

	enum class Relevance { Invalid = -1, Nobody, Monster, Light, Heavy };
	Relevance relevance = Relevance::Invalid;

	std::vector<std::string> backstory;


	Character() : CampaignElem(count++) { name = "Character"; }
	Character(const nlohmann::json& data) : CampaignElem(0) { deserialize(data); }

	nlohmann::json serialize() const;
	void deserialize(const nlohmann::json& data);
};