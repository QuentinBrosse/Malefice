#include <iterator>
#include "SpellManager.h"

namespace ecs
{
	SpellManager::SpellManager() : AComponent("SpellManager", ecs::ComponentType::SPELL_MANAGER),
		m_spells(), m_currentSpell(m_spells.end()), m_weaponManager(), m_weaponsIsCurrent(false)
	{
	}

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
		os << "SpellManager {spells = [";
		for (auto it = m_spells.begin(); it != m_spells.end(); ++it)
		{
			os << "Pair {SpellType = " << it->first << ", Spell = ";
			it->second.dump(os);
			os << "}" << (std::next(it) != m_spells.end() ? ", " : "");
		}
		os << "], currentSpell = ";
		if (m_currentSpell != m_spells.end())
		{
			os << "Pair {SpellType = " << m_currentSpell->first << ", Spell = ";
			m_currentSpell->second.dump(os);
			os << "}";
		}
		else
		{
			os << "N/A";
		}
		os << ", weaponManager = " << m_weaponManager << ", weaponIsCurrent = " << m_weaponsIsCurrent << "}";
	}


	void	SpellManager::serialize(RakNet::BitStream& out)	const
	{
		// TODO: implement serialization
	}

	void	SpellManager::deserialize(RakNet::BitStream& in)
	{
		// TODO: implement deserialization
	}
}
