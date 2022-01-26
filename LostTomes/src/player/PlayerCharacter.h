#pragma once

typedef const uint32_t Modifier;


struct Accumulable
{
	const uint32_t maximum;
	uint32_t current;

	void operator++() { current += (current < maximum); }
	void operator+=(uint32_t amount) { current = min(current + amount, maximum); }

	void operator--() { current -= (current > 0); }
	void operator-=(uint32_t amount) { current = max(current - amount, 0); }

	Accumulable(uint32_t _max) : maximum(_max), current(_max) { }
};


struct PlayerClass
{
	template<typename Ty>
	using TableElement = std::unordered_map<std::string, std::array<Ty, 20>>;

	const uint32_t hitDice;
	const uint32_t savingThrows;

	const uint32_t casterType;
	const size_t casterAbility;

	TableElement<Modifier> modifiers;
	TableElement<Accumulable> accumulables;

	PlayerClass(const nlohmann::json& j)
		: hitDice(j["hit-dice"]), savingThrows(getSavingThrows(j["saving-throws"][0])), casterType(j["caster-type"]), casterAbility(j["caster-ability"])
	{}

private:
	int getSavingThrows(const nlohmann::json& j)
	{
		uint32_t result = 0;
		result &= 1 << j[0];
		result &= 1 << j[1];
		return result;
	}
};


struct PlayerRace
{

};


class PlayerCharacter
{
public:
	enum class Ability
	{
		STR = 0,
		DEX = 1,
		CON = 2,
		INT = 3,
		WIS = 4,
		CHA = 5
	};

	enum class Skill
	{
		Acrobatics			= 0,
		AnimalHandling		= 1,
		Arcana				= 1 << 1,
		Athletics			= 1 << 2,
		Deception			= 1 << 3,
		History				= 1 << 4,
		Insight				= 1 << 5,
		Intimidation		= 1 << 6,
		Investigation		= 1 << 7,
		Medicine			= 1 << 8,
		Nature				= 1 << 9,
		Perception			= 1 << 10,
		Performance			= 1 << 11,
		Persuasion			= 1 << 12,
		Religion			= 1 << 13,
		SleightOfHand		= 1 << 14,
		Stealth				= 1 << 15,
		Survival			= 1 << 16
	};

private:
	uint32_t m_level = 0;

	uint32_t m_scores[6] = { 0 };
	int m_abilities[6] = { 0 };
	uint32_t m_skills = 0;

	uint32_t m_hitPoints = 0;
	uint32_t m_armorClass = 0;

	uint32_t m_currency[4] = { 0 };

	PlayerRace m_race;
	PlayerClass m_class;

	std::unordered_map<Skill, Ability> skillToAbility;

	int getProficiencyBonus();
	void updateModifier(Ability ability);

	nlohmann::json getClass(const std::string& className);
	void init();

public:
	PlayerCharacter(const std::string& className);
	PlayerCharacter(const nlohmann::json& character);

	void toggleSkill(Skill skill);
	int getSkillModifier(Skill skill);
	int getSavingThrowModifier(Ability ability);
	int getSpellAttackModifier()
	{
		if (m_class.casterType != 0)
			return m_abilities[m_class.casterAbility] + getProficiencyBonus();
	}
	int getSpellSaveDC()
	{
		if (m_class.casterType != 0)
			return m_abilities[m_class.casterAbility] + getProficiencyBonus() + 8;
	}
};