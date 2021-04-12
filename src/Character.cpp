#include "PCH.h"

#include "Character.h"


uint32_t Character::count = 0;


nlohmann::json Character::serialize() const
{
	nlohmann::json result;

	result["number"] = (int)number;

	result["name"] = name;
	result["relevance"] = (uint32_t)relevance;

	result["backstory"] = nlohmann::json::array();
	for (const auto& bs : backstory)
		result["backstory"].push_back(bs);

	result["refs"] = nlohmann::json::array();
	for (const auto& ref : references)
		result["refs"].push_back(ref->name);

	return result;
}

void Character::deserialize(const nlohmann::json& data)
{
	number = (uint32_t)data["number"];

	name = data["name"];
	relevance = (Relevance)data["relevance"];

	for (const auto& bs : data["backstory"])
		backstory.push_back(bs);

	references = findRefs(&data["refs"]);

	count++;
}