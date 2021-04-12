#pragma once


struct CampaignElem
{
	uint32_t number;
	std::string name;
	std::vector<CampaignElem*> references;


	CampaignElem(uint32_t _number) : number(_number) {}

	virtual nlohmann::json serialize() const = 0;
	virtual void deserialize(const nlohmann::json& data) = 0;
};


std::vector<CampaignElem*> findRefs(nlohmann::json const* refNames = nullptr);