#include "PCH.h"

#include "CampaignElem.h"


uint32_t Element::count[4] = { 0 };


Element::Element(uint32_t _type) : type(_type), number(count[_type]++)
{ 
	name = "Element_" + std::to_string(number);
}

Element::Element(uint32_t _type, const nlohmann::json& data) : type(_type), number(0)
{
	deserialize(data);
}


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