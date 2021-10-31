#include "PCH.h"
#include "PlayerCharacter.h"


int PlayerCharacter::getProficiencyBonus()
{
	return (m_level - 1) / 4 + 2;
}

void PlayerCharacter::updateModifier(Ability ability)
{
	m_abilities[(size_t)ability] = m_scores[(size_t)ability] / 2 - 5;
}

nlohmann::json PlayerCharacter::getClass(const std::string& className)
{
	std::ifstream stream("res/classes.json");
	nlohmann::json j;
	stream >> j;
	stream.close();

	return j[className];
}

void PlayerCharacter::init()
{
	skillToAbility[Skill::Acrobatics] = (Ability)1;
	skillToAbility[Skill::AnimalHandling] = (Ability)4;
	skillToAbility[Skill::Arcana] = (Ability)3;
	skillToAbility[Skill::Athletics] = (Ability)0;
	skillToAbility[Skill::Deception] = (Ability)5;
	skillToAbility[Skill::History] = (Ability)3;
	skillToAbility[Skill::Insight] = (Ability)4;
	skillToAbility[Skill::Intimidation] = (Ability)5;
	skillToAbility[Skill::Investigation] = (Ability)3;
	skillToAbility[Skill::Medicine] = (Ability)4;
	skillToAbility[Skill::Nature] = (Ability)3;
	skillToAbility[Skill::Perception] = (Ability)4;
	skillToAbility[Skill::Performance] = (Ability)5;
	skillToAbility[Skill::Persuasion] = (Ability)5;
	skillToAbility[Skill::Religion] = (Ability)3;
	skillToAbility[Skill::SleightOfHand] = (Ability)1;
	skillToAbility[Skill::Stealth] = (Ability)1;
	skillToAbility[Skill::Survival] = (Ability)4;
}


PlayerCharacter::PlayerCharacter(const std::string& className)
	: m_class(getClass(className))
{}

PlayerCharacter::PlayerCharacter(const nlohmann::json& character)
	: m_class(character["class"]), m_level(character["level"])
{}


void PlayerCharacter::toggleSkill(Skill skill)
{
	if (m_skills & (uint32_t)skill)
		m_skills ^= (uint32_t)skill;
	else
		m_skills &= (uint32_t)skill;
}

int PlayerCharacter::getSkillModifier(Skill skill)
{
	return m_abilities[(size_t)skillToAbility[skill]] + (getProficiencyBonus() * (m_skills & (uint32_t)skill));
}

int PlayerCharacter::getSavingThrowModifier(Ability ability)
{
	uint32_t abilityAsPow2 = (1 << (int)ability) >> 1;

	return m_abilities[(size_t)ability] + getProficiencyBonus() * (abilityAsPow2 & m_class.savingThrows);
}