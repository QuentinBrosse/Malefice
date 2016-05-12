#include <iostream>
#include "Spell.h"

namespace ecs
{
	Spell::Spell() : AComponent("Spell", SPELL),
		ID(0), SPELL_NAME("default"), m_spellType(Spell::NOTHING), COOLDOWN(0)
	{
		m_isLock = false;
	}

	Spell::Spell(const int id, const std::string& name, const Spell::SpellType spellType, const int coolDown) : AComponent("Spell", SPELL),
		ID(id), SPELL_NAME(name), m_spellType(spellType), COOLDOWN(coolDown)
	{
		m_isLock = false;
	}

	Spell::Spell(const Spell& cpy): AComponent("Spell", SPELL),
		ID(cpy.ID), SPELL_NAME(cpy.SPELL_NAME), m_spellType(cpy.m_spellType), COOLDOWN(cpy.COOLDOWN)
	{
		m_isLock = false;
	}

	const Spell::SpellType	Spell::getSpellType() const
	{
		return m_spellType;
	}

	void Spell::setSpellType(const SpellType newSpellType)
	{
		m_spellType = newSpellType;
	}

	bool Spell::isLock() const
	{
		return m_isLock;
	}

	void Spell::lock()
	{
		m_isLock = true;
	}

	void Spell::unlock()
	{
		m_isLock = false;
	}


	void	Spell::dump(std::ostream& os)	const
	{
		os << "[" << NAME << ": " << m_spellType << "/" << COOLDOWN << "]";
	}
}
