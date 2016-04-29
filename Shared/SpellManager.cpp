#include "SpellManager.h"
#include <utility>

namespace ecs
{
	SpellManager::SpellManager(const Spell& defaultSpell) : AComponent("SpellManager", SPELL_MANAGER)
	{
		m_spells.insert(std::pair<Spell::SpellType, Spell>(defaultSpell.getSpellType(), defaultSpell));
		m_currentSpell = m_spells.begin();
	}

	Spell& SpellManager::getCurrentSpell() const
	{
		return m_currentSpell->second;
	}

	void SpellManager::addSpell(const Spell& newSpell)
	{
		if (m_spells.find(newSpell.getSpellType()) == m_spells.end())
			m_spells.insert(std::pair<Spell::SpellType, Spell>(newSpell.getSpellType(), newSpell));
	}

	void SpellManager::changeToNextSpell()
	{
		++m_currentSpell;
		if (m_currentSpell == m_spells.end())
			m_currentSpell = m_spells.begin();
	}

	void SpellManager::changeToPrecSpell()
	{
		if (m_currentSpell == m_spells.begin())
			m_currentSpell = --(m_spells.end());
		else
			--m_currentSpell;
	}

	void SpellManager::dump() const
	{
		for (auto& spell : m_spells)
			spell.second.dump();
	}
}
