#include "SpellManager.h"

namespace ecs
{
	//TODO: CHange new Weapon with call to WeaponCreator
	SpellManager::SpellManager(const Spell& defaultSpell) : AComponent("SpellManager", SPELL_MANAGER),
		m_weaponManager(*(new Weapon(1, "shotgun", 100, 50, 50, 100, 10, 5, Weapon::WeaponType::SHOTGUN, false)))
	{
		m_spells.insert(std::pair<Spell::SpellType, Spell>(defaultSpell.getSpellType(), defaultSpell));
		m_currentSpell = m_spells.begin();
		m_weaponManager.addWeapon(*(new Weapon(1, "knife", 0, 0, 50, 0, 0, 0, Weapon::WeaponType::KNIFE, true)));
	}

	Spell& SpellManager::getCurrentSpell() const
	{
		return m_currentSpell->second;
	}

	bool SpellManager::weaponsIsCurrent() const
	{
		return m_weaponsIsCurrent;
	}

	void SpellManager::changeCurrentManager()
	{
		m_weaponsIsCurrent = !m_weaponsIsCurrent;
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

	Weapon& SpellManager::getCurrentWeapon() const
	{
		return m_weaponManager.getCurrentWeapon();
	}

	void SpellManager::changeToNextWeapon()
	{
		m_weaponManager.changeToNextWeapon();
	}

	void SpellManager::changeToPrecWeapon()
	{
		m_weaponManager.changeToPrecWeapon();
	}

	void	SpellManager::dump(std::ostream& os)	const
	{
		for (auto& spell : m_spells)
			spell.second.dump(os);
	}
}
