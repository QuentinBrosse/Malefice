#include "WeaponManager.h"

namespace ecs
{
	WeaponManager::WeaponManager() : AComponent("WeaponManager", ecs::ComponentType::WEAPON_MANAGER)
	{
	}

	WeaponManager::WeaponManager(const Weapon& defaultWeapon) : AComponent("WeaponManager", WEAPON_MANAGER)
	{
		m_weapons.insert(std::pair<Weapon::WeaponType, Weapon> (defaultWeapon.getWeaponType(), defaultWeapon));
		m_currentWeapon = m_weapons.begin();
	}

	void	WeaponManager::addWeapon(const Weapon& newWeapon)
	{
		if (m_weapons.find(newWeapon.getWeaponType()) == m_weapons.end())
			m_weapons.insert(std::pair<Weapon::WeaponType, Weapon> (newWeapon.getWeaponType(), newWeapon));
	}

	
	void WeaponManager::changeToNextWeapon()
	{
		++m_currentWeapon;
		if (m_currentWeapon == m_weapons.end())
			m_currentWeapon = m_weapons.begin();
	}

	void WeaponManager::changeToPrecWeapon()
	{
		if (m_currentWeapon == m_weapons.begin())
			m_currentWeapon = --(m_weapons.end());
		else
			--m_currentWeapon;
	}

	Weapon&	WeaponManager::getCurrentWeapon() const
	{
		return m_currentWeapon->second;
	}

	void	WeaponManager::dump(std::ostream& os)	const
	{
		for (auto& weapon : m_weapons)
			weapon.second.dump(os);
	}


	void	WeaponManager::serialize(RakNet::BitStream& out)	const
	{
		// TODO: implement serialization
	}

	void	WeaponManager::deserialize(RakNet::BitStream& in)
	{
		// TODO: implement deserialization
	}
};
