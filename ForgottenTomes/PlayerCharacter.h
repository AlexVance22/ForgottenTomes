#pragma once


typedef const uint32_t Modifier;

struct Accumulable
{
	const uint32_t maximum;
	uint32_t current;

	Accumulable(uint32_t _max) : maximum(_max), current(_max) { }
};


struct PlayerClass
{
	template<typename Ty>
	using TableElement = std::unordered_map<std::string, std::array<Ty, 20>>;


	uint32_t baseHitPoints;

	TableElement<Modifier> modifiers;
	TableElement<Accumulable> accumulables;

	PlayerClass(uint32_t _baseHitPoints) : baseHitPoints(_baseHitPoints) {}
};


struct PlayerRace
{

};


class PlayerCharacter
{
public:
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
	uint32_t m_abilities[6] = { 0 };
	uint32_t m_skills = 0;

	uint32_t m_hitPoints = 0;
	uint32_t m_armorClass = 0;

	uint32_t m_currency[4] = { 0 };

	std::unique_ptr<PlayerRace> m_race;
	std::unique_ptr<PlayerClass> m_class;

	std::unordered_map<Skill, size_t> skillToAbility;

	int getProficiencyBonus() { return (m_level - 1) / 4 + 2; }

	void initDefault()
	{
		skillToAbility[Skill::Acrobatics] =
		skillToAbility[Skill::AnimalHandling] =
		skillToAbility[Skill::Arcana] =
		skillToAbility[Skill::Athletics] =
		skillToAbility[Skill::Deception] =
		skillToAbility[Skill::History] =
		skillToAbility[Skill::Insight] =
		skillToAbility[Skill::Intimidation] =
		skillToAbility[Skill::Investigation] =
		skillToAbility[Skill::Medicine] =
		skillToAbility[Skill::Nature] =
		skillToAbility[Skill::Perception] =
		skillToAbility[Skill::Performance] =
		skillToAbility[Skill::Persuasion] =
		skillToAbility[Skill::Religion] =
		skillToAbility[Skill::SleightOfHand] =
		skillToAbility[Skill::Stealth] =
		skillToAbility[Skill::Survival] =
	}

	void load()
	{
	}

public:
	PlayerCharacter() {}
	PlayerCharacter(uint32_t level) : m_level(level) {}

	void toggleSkill(Skill skill)
	{
		if (m_skills & (uint32_t)skill)
			m_skills ^= (uint32_t)skill;
		else
			m_skills &= (uint32_t)skill;
	}
	int getSkillModifier(Skill skill)
	{
	}
};