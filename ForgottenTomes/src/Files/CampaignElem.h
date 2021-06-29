#pragma once


struct Element
{
	static uint32_t count[4];

	uint32_t type = 0;
	uint32_t number;
	std::string name;
	std::vector<std::string> content;

	enum class Relevance { Invalid = -1, Throwaway, Small, Notable, Prominent, Critical };
	Relevance relevance = Relevance::Invalid;


	Element(uint32_t _type) : type(_type), number(count[_type]++) { name = "Element" + std::to_string(number); }
	Element(const nlohmann::json& data) : number(0) { deserialize(data); }

	nlohmann::json serialize() const;
	void deserialize(const nlohmann::json& data);
};