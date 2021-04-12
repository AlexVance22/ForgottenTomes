#include "PCH.h"

#include "Location.h"


uint32_t Location::count = 0;


nlohmann::json Location::serialize() const
{
	nlohmann::json result;

	result["number"] = (int)number;

	result["name"] = name;
	result["size"] = (uint32_t)size;

	result["prehistory"] = nlohmann::json::array();
	for (const auto& ph : prehistory)
		result["prehistory"].push_back(ph);

	result["posthistory"] = nlohmann::json::array();
	for (const auto& ph : posthistory)
		result["posthistory"].push_back(ph);

	result["refs"] = nlohmann::json::array();
	for (const auto& ref : references)
		result["refs"].push_back(ref->name);

	return result;
}

void Location::deserialize(const nlohmann::json& data)
{
	number = (uint32_t)data["number"];

	name = data["name"];
	size = (Size)data["size"];

	for (const auto& ph : data["prehistory"])
		prehistory.push_back(ph);

	for (const auto& ph : data["posthistory"])
		posthistory.push_back(ph);

	references = findRefs(&data["refs"]);

	count++;
}