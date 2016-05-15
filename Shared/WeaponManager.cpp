#include "WeaponManager.h"

namespace ecs
{
	WeaponManager::WeaponManager() : AComponent("WeaponManager", ecs::ComponentType::WEAPON_MANAGER)
	{
	}

	WeaponManager::WeaponManager(Weapon& defaultWeapon) : AComponent("WeaponManager", WEAPON_MANAGER)
	{
		m_weapons.insert(std::pair<Weapon::WeaponType, Weapon&> (defaultWeapon.getWeaponType(), defaultWeapon));
		m_currentWeapon = m_weapons.begin();
	}

	void	WeaponManager::addWeapon(Weapon& newWeapon)
	{
		if (m_weapons.find(newWeapon.getWeaponType()) == m_weapons.end())
			m_weapons.insert(std::pair<Weapon::WeaponType, Weapon&> (newWeapon.getWeaponType(), newWeapon));
	}

	
	void WeaponManager::changeToNextWeapon()
	{
		m_currentWeapon->second.setActivity(false);
		++m_currentWeapon;
		if (m_currentWeapon == m_weapons.end())
			m_currentWeapon = m_weapons.begin();
		m_currentWeapon->second.setActivity(true);
	}

	void WeaponManager::changeToPrecWeapon()
	{
		m_currentWeapon->second.setActivity(false);
		if (m_currentWeapon == m_weapons.begin())
			m_currentWeapon = --(m_weapons.end());
		else
			--m_currentWeapon;
		m_currentWeapon->second.setActivity(true);
	}

	Weapon&	WeaponManager::getCurrentWeapon() const
	{
		return m_currentWeapon->second;
	}

	std::map<Weapon::WeaponType, Weapon&>& WeaponManager::getWeapons()
	{
		return m_weapons;
	}

	void WeaponManager::createWeapon(irr::IrrlichtDevice * device, const std::string & newNameTexture, const std::string & newNameMesh, const Weapon& weaponCpy)
	{
		Weapon*	weapon = new Weapon(weaponCpy);

		weapon->createScene(device, newNameTexture, newNameMesh, false);
		addWeapon(*weapon);
		if (m_weapons.size() == 1)
			m_currentWeapon = m_weapons.begin();
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
