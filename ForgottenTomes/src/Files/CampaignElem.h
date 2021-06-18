#pragma once


struct Element
{
	static uint32_t count;

	uint32_t number;
	std::string name;
	std::vector<std::string> content;

	enum class Relevance { Invalid = -1, Throwaway, Small, Notable, Prominent, Critical };
	Relevance relevance = Relevance::Invalid;


	Element() : number(count++) { name = "Element" + std::to_string(number); }
	Element(const nlohmann::json& data) : number(0) { deserialize(data); }

	nlohmann::json serialize() const;
	void deserialize(const nlohmann::json& data);
};