#include "WeaponManager.h"

namespace ecs
{
	WeaponManager::WeaponManager() : AComponent("WeaponManager", ecs::AComponent::ComponentType::WEAPON_MANAGER),
		m_weapons(), m_currentWeapon(m_weapons.end())
	{
	}

	WeaponManager::WeaponManager(Weapon& defaultWeapon) : AComponent("WeaponManager", ecs::AComponent::ComponentType::WEAPON_MANAGER),
		m_weapons(), m_currentWeapon(m_weapons.end())
	{
		init(defaultWeapon);
	}


	void	WeaponManager::init(Weapon& defaultWeapon)
	{
		m_weapons.insert(std::pair<Weapon::WeaponType, Weapon&>(defaultWeapon.getWeaponType(), defaultWeapon));
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

	void WeaponManager::createWeapon(irr::IrrlichtDevice* device, const Weapon& weaponCpy)
	{
		Weapon*	weapon = new Weapon(weaponCpy);

		weapon->createScene(device, false);
		addWeapon(*weapon);
		if (m_weapons.size() == 1)
			m_currentWeapon = m_weapons.begin();
	}

	void	WeaponManager::dump(std::ostream& os)	const
	{
		os << "WeaponManager {weapons = [";
		for (auto it = m_weapons.begin(); it != m_weapons.end(); ++it)
		{
			os << "Pair {WeaponType = " << it->first << ", Weapon = ";
			it->second.dump(os);
			os << "}" << (std::next(it) != m_weapons.end() ? ", " : "");
		}
		os << "], currentWeapon = ";
		if (m_currentWeapon != m_weapons.end())
		{
			os << "Pair {WeaponType = " << m_currentWeapon->first << ", Weapon = ";
			m_currentWeapon->second.dump(os);
			os << "}";
		}
		else
		{
			os << "N/A";
		}
		os << "}";
	}

	AComponent& WeaponManager::affect(const AComponent& rhs)
	{
		const WeaponManager& weaponManager = dynamic_cast<const WeaponManager&>(rhs);

		m_currentWeapon = weaponManager.m_currentWeapon;
		m_weapons = weaponManager.m_weapons;

		return *this;
	}


	void	WeaponManager::serialize(RakNet::BitStream& out, bool serializeType)	const
	{
		AComponent::serialize(out, serializeType);
		out.Write(m_currentWeapon->first);
		out.Write<size_t>(m_weapons.size());
		for (auto it = m_weapons.begin(); it != m_weapons.end(); it++)
		{
			out.Write(it->first);
			it->second.serialize(out, serializeType);
		}
	}

	void	WeaponManager::deserialize(RakNet::BitStream& in)
	{
		size_t nb_weapon;
		Weapon::WeaponType current_weapon_type;
		Weapon::WeaponType weapon_type;

		
		AComponent::deserialize(in);
		in.Read(current_weapon_type);
		in.Read(nb_weapon);
		for (size_t i = 0; i < nb_weapon; i++)
		{
			in.Read(weapon_type);
			m_weapons.emplace(weapon_type, *(new Weapon()));
			m_weapons.at(weapon_type).deserialize(in);
		}
		m_currentWeapon = m_weapons.find(current_weapon_type);
	}
};
