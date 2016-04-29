#include "WeaponManager.h"

namespace ecs
{
	WeaponManager::WeaponManager(const Weapon& cDefaultWeapon) : AComponent("WeaponManager", WEAPON_MANAGER)
	{
		m_lWeapons.push_back(cDefaultWeapon);
		//m_currentWeapon = m_lWeapons.begin();
	}

	void	WeaponManager::addWeapon(const Weapon& cNewWeapon)
	{
		m_lWeapons.push_back(cNewWeapon);
	}

	
	void WeaponManager::changeToNextWeapon()
	{
		++m_currentWeapon;
		if (m_currentWeapon == m_lWeapons.end())
			m_currentWeapon = m_lWeapons.begin();
	}

	void WeaponManager::changeToPrecWeapon()
	{
		if (m_currentWeapon == m_lWeapons.begin())
			m_currentWeapon = --(m_lWeapons.end());
		else
			--m_currentWeapon;
	}

	const Weapon&	WeaponManager::getCurrentWeapon() const
	{
		return *(m_currentWeapon);
	}

	void WeaponManager::dump() const
	{
		for (auto it = m_lWeapons.begin(); it != m_lWeapons.end(); --it)
		{
			(*it).dump();
		}
	}
};
