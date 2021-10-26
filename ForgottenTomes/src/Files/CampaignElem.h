#pragma once


struct Element
{
	static uint32_t count[4];

	uint32_t type;
	uint32_t number;
	std::string name;
	std::vector<std::string> content;

	enum class Relevance { Invalid = -1, Throwaway, Small, Notable, Prominent, Critical };
	Relevance relevance = Relevance::Invalid;


	Element(uint32_t _type);
	Element(uint32_t _type, const nlohmann::json& data);

	nlohmann::json serialize() const;
	void deserialize(const nlohmann::json& data);
};