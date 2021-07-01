#pragma once


typedef const uint32_t Modifier;
struct Accumulable
{
	const uint32_t maximum;
	uint32_t current;

	void operator++() { current += (current < maximum); }
	void operator+=(uint32_t amount) { current = min(current + amount, maximum); }

	void operator--() { current -= (current > 0); }
	void operator-=(uint32_t amount) { current = max((int)current - amount, 0); }

	Accumulable(uint32_t _max) : maximum(_max), current(_max) { }
};


struct PlayerClass
{
	template<typename Ty>
	using TableElement = std::unordered_map<std::string, std::array<Ty, 20>>;

	const uint32_t hitDice;
	const uint32_t savingThrows;

	const uint32_t casterType;

	TableElement<Modifier> modifiers;
	TableElement<Accumulable> accumulables;

	int getSavingThrows(const nlohmann::json& j)
	{
		uint32_t result = 0;
		result &= 1 << j[0];
		result &= 1 << j[1];
		return result;
	}

	PlayerClass(const nlohmann::json& j) 
		: hitDice(j["hit-dice"]), savingThrows(getSavingThrows(j["saving-throws"][0])), casterType(j["spellcasting-level"]) 
	{}
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

	int getProficiencyBonus() { return (m_level - 1) / 4 + 2; }
	void updateModifier(Ability ability)
	{
		m_abilities[(size_t)ability] = m_scores[(size_t)ability] / 2 - 5;
	}

	nlohmann::json getClass(const std::string& className)
	{
		std::ifstream stream("res/classes.json");
		nlohmann::json j;
		stream >> j;
		stream.close();

		return j[className];
	}
	void init()
	{
		skillToAbility[Skill::Acrobatics] =		(Ability)1;
		skillToAbility[Skill::AnimalHandling] = (Ability)4;
		skillToAbility[Skill::Arcana] =			(Ability)3;
		skillToAbility[Skill::Athletics] =		(Ability)0;
		skillToAbility[Skill::Deception] =		(Ability)5;
		skillToAbility[Skill::History] =		(Ability)3;
		skillToAbility[Skill::Insight] =		(Ability)4;
		skillToAbility[Skill::Intimidation] =	(Ability)5;
		skillToAbility[Skill::Investigation] =	(Ability)3;
		skillToAbility[Skill::Medicine] =		(Ability)4;
		skillToAbility[Skill::Nature] =			(Ability)3;
		skillToAbility[Skill::Perception] =		(Ability)4;
		skillToAbility[Skill::Performance] =	(Ability)5;
		skillToAbility[Skill::Persuasion] =		(Ability)5;
		skillToAbility[Skill::Religion] =		(Ability)3;
		skillToAbility[Skill::SleightOfHand] =	(Ability)1;
		skillToAbility[Skill::Stealth] =		(Ability)1;
		skillToAbility[Skill::Survival] =		(Ability)4;
	}

public:
	PlayerCharacter(const std::string& className) : m_class(getClass(className)) {}
	PlayerCharacter(const nlohmann::json& character) : m_class(character["class"]), m_level(character["level"]) {}

	void toggleSkill(Skill skill)
	{
		if (m_skills & (uint32_t)skill)
			m_skills ^= (uint32_t)skill;
		else
			m_skills &= (uint32_t)skill;
	}
	int getSkillModifier(Skill skill)
	{
		return m_abilities[(size_t)skillToAbility[skill]] + (getProficiencyBonus() * (m_skills & (uint32_t)skill));
	}
	int getSavingThrowModifier(Ability ability)
	{
		uint32_t abilityAsPow2 = (1 << (int)ability) >> 1;

		return m_abilities[(size_t)ability] + getProficiencyBonus() * (abilityAsPow2 & m_class.savingThrows);
	}
};