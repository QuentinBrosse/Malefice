#include <iostream>
#include "Spell.h"

namespace ecs
{
	Spell::Spell() : AComponent("Spell", SPELL),
		m_spellType(Spell::NOTHING)
	{

	}

	Spell::Spell(const Spell::SpellType spellType) : AComponent("Spell", SPELL),
		m_spellType(spellType)
	{

	}

	Spell::Spell(const Spell& cpy): AComponent("Spell", SPELL),
		m_spellType(cpy.m_spellType)
	{
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

	void Spell::dump() const
	{
		std::cout << "[" << NAME << ": " << m_spellType << "]" << std::endl;
	}
}