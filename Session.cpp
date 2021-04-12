#include "PCH.h"

#include "Session.h"


uint32_t Session::count = 0;


nlohmann::json Session::serialize() const
{
	nlohmann::json result;

	result["number"] = (int)number;

	result["name"] = name;

	result["elems"] = nlohmann::json::array();
	for (const auto& el : elems)
		result["elems"].push_back(el);

	result["refs"] = nlohmann::json::array();
	for (const auto& ref : references)
		result["refs"].push_back(ref->name);

	return result;
}

void Session::deserialize(const nlohmann::json& data)
{
	number = (uint32_t)data["number"];

	name = data["name"];

	for (const auto& el : data["elems"])
		elems.push_back(el);

	references = findRefs(&data["refs"]);

	count++;
}