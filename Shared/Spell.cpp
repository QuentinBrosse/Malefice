#include <iostream>
#include "Spell.h"

namespace ecs
{
	Spell::Spell() : AComponent("Spell", SPELL),
		m_spellType(Spell::NOTHING), COOLDOWN(0)
	{
		m_isLock = false;
	}

	Spell::Spell(const Spell::SpellType spellType, const int coolDown) : AComponent("Spell", SPELL),
		m_spellType(spellType), COOLDOWN(coolDown)
	{
		m_isLock = false;
	}

	Spell::Spell(const Spell& cpy): AComponent("Spell", SPELL),
		m_spellType(cpy.m_spellType), COOLDOWN(cpy.COOLDOWN)
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

	void Spell::dump() const
	{
		std::cout << "[" << NAME << ": " << m_spellType << "]" << std::endl;
	}
}