#include "PCH.h"

#include "CampaignElem.h"


uint32_t Element::count[4] = { 0 };


nlohmann::json Element::serialize() const
{
	nlohmann::json result;

	result["number"] = (int)number;
	result["name"] = name;

	result["content"] = nlohmann::json::array();
	for (const auto& ct : content)
		result["content"].push_back(ct);

	return result;
}

void Element::deserialize(const nlohmann::json& data)
{
	number = (uint32_t)data["number"];
	name = data["name"];

	for (const auto& ct : data["content"])
		content.push_back(ct);

	count[type]++;
}