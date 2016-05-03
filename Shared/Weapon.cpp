#include <iostream>
#include "Weapon.h"

namespace ecs
{
	Weapon::Weapon() : AComponent("Weapon", WEAPON),
		WEAPON_NAME("Weapon"), MAX_AMMUNITION(0), MAX_AMMUNITION_EXPLOSIVE(0), DAMAGE(0), DAMAGE_EXPLOSIVE(0), MAX_AMMUNITION_LOADER(0), MAX_AMMUNITION_EXPLOSIVE_LOADER(0), WEAPON_TYPE(DEFAULT), IS_GUN(false)
	{
		m_currentAmmunition = MAX_AMMUNITION;
		m_currentAmmunitionExplosive = MAX_AMMUNITION_EXPLOSIVE;
	}

	Weapon::Weapon(const std::string& name, const int maxAmmunition, const int maxAmmunitionExplosive, const int damage, const int damageExplosive, const int maxAmmunitionLoader, const int maxAmmunitionExplosiveLoader, const WeaponType weaponType, const bool isGun) : AComponent("Weapon", WEAPON),
		WEAPON_NAME(name), MAX_AMMUNITION(maxAmmunition), MAX_AMMUNITION_EXPLOSIVE(maxAmmunitionExplosive), DAMAGE(damage), DAMAGE_EXPLOSIVE(damageExplosive), MAX_AMMUNITION_LOADER(maxAmmunitionLoader), MAX_AMMUNITION_EXPLOSIVE_LOADER(maxAmmunitionExplosiveLoader), WEAPON_TYPE(weaponType), IS_GUN(isGun)
	{
		m_currentAmmunition = MAX_AMMUNITION;
		m_currentAmmunitionExplosive = MAX_AMMUNITION_EXPLOSIVE;
		m_currentAmmunitionLoader = MAX_AMMUNITION_LOADER;
		m_currentAmmunitionExplosiveLoader = MAX_AMMUNITION_EXPLOSIVE_LOADER;
	}

	Weapon::Weapon(const Weapon& cpy) : AComponent("Weapon", WEAPON),
		WEAPON_NAME(cpy.NAME), MAX_AMMUNITION(cpy.MAX_AMMUNITION), MAX_AMMUNITION_EXPLOSIVE(cpy.MAX_AMMUNITION_EXPLOSIVE), DAMAGE(cpy.DAMAGE), DAMAGE_EXPLOSIVE(cpy.DAMAGE_EXPLOSIVE), MAX_AMMUNITION_LOADER(cpy.MAX_AMMUNITION_LOADER), MAX_AMMUNITION_EXPLOSIVE_LOADER(cpy.MAX_AMMUNITION_EXPLOSIVE_LOADER),  WEAPON_TYPE(cpy.WEAPON_TYPE), IS_GUN(cpy.IS_GUN)
	{
		m_currentAmmunition = cpy.m_currentAmmunition;
		m_currentAmmunitionExplosive = cpy.m_currentAmmunitionExplosive;
		m_currentAmmunitionLoader = cpy.m_currentAmmunitionLoader;
		m_currentAmmunitionExplosiveLoader = cpy.m_currentAmmunitionExplosiveLoader;
	}

	Weapon& Weapon::operator=(const Weapon& other)
	{
		m_currentAmmunition = other.m_currentAmmunition;
		m_currentAmmunitionExplosive = other.m_currentAmmunitionExplosive;
		m_currentAmmunitionLoader = other.m_currentAmmunitionLoader;
		m_currentAmmunitionExplosiveLoader = other.m_currentAmmunitionExplosiveLoader;
		return *this;
	}

	void	Weapon::dump() const
	{
		std::cout << "[" << NAME << "/" << m_currentAmmunition << "/" << MAX_AMMUNITION << "/" << m_currentAmmunitionExplosive << "/" << MAX_AMMUNITION_EXPLOSIVE << "/" << DAMAGE << "/" << DAMAGE_EXPLOSIVE <<"]" << std::endl;
	}

	const int		Weapon::getDamage() const
	{
		return DAMAGE;
	}

	const int		Weapon::getDamageExplosive() const
	{
		return DAMAGE_EXPLOSIVE;
	}

	int			Weapon::getAmmunition() const
	{
		return m_currentAmmunition;
	}

	int			Weapon::getAmmunitionExplosive() const
	{
		return m_currentAmmunitionExplosive;
	}

	int Weapon::getAmmunitionLoader() const
	{
		return m_currentAmmunitionLoader;
	}

	int Weapon::getAmmunitionExplosiveLoader() const
	{
		return m_currentAmmunitionExplosiveLoader;
	}

	void Weapon::reload()
	{
		if (m_currentAmmunition != 0 && m_currentAmmunitionLoader < MAX_AMMUNITION_LOADER)
		{
			int nbAmmunition = MAX_AMMUNITION_LOADER - m_currentAmmunitionLoader;
			if (m_currentAmmunition >= nbAmmunition)
			{
				m_currentAmmunitionLoader = MAX_AMMUNITION_EXPLOSIVE_LOADER;
				decAmmunition(nbAmmunition);
			}
			else
			{
				m_currentAmmunitionLoader = m_currentAmmunition;
				m_currentAmmunition = 0;
			}
		}

	}

	void Weapon::reloadExplosive()
	{
		if (m_currentAmmunitionExplosive != 0 && m_currentAmmunitionExplosiveLoader < MAX_AMMUNITION_EXPLOSIVE_LOADER)
		{
			int nbAmmunition = MAX_AMMUNITION_EXPLOSIVE_LOADER - m_currentAmmunitionExplosiveLoader;
			if (nbAmmunition <= m_currentAmmunitionExplosive)
			{
				m_currentAmmunitionExplosiveLoader = MAX_AMMUNITION_EXPLOSIVE_LOADER;
				decAmmunitionExplosive(nbAmmunition);
			}
			else
			{
				m_currentAmmunitionExplosiveLoader = m_currentAmmunitionExplosive;
				m_currentAmmunitionExplosive = 0;
			}
		}
	}

	void Weapon::fired()
	{
		m_currentAmmunitionExplosiveLoader--;
	}

	void Weapon::firedExplosive()
	{
		m_currentAmmunitionExplosiveLoader--;
	}

	const Weapon::WeaponType Weapon::getWeaponType() const
	{
		return WEAPON_TYPE;
	}

	const bool		Weapon::isGun() const
	{
		return IS_GUN;
	}
	const std::string & Weapon::getName() const
	{
		return WEAPON_NAME;
	}

	void Weapon::decAmmunition(int nbLoaded)
	{
		m_currentAmmunition -= nbLoaded;
		if (m_currentAmmunition < 0)
			m_currentAmmunition = 0;
	}

	void Weapon::decAmmunitionExplosive(int nbLoaded)
	{
		m_currentAmmunitionExplosive -= nbLoaded;
		if (m_currentAmmunitionExplosive < 0)
			m_currentAmmunitionExplosive = 0;
	}

	void Weapon::incAmmunition(int nbAmmuition)
	{
		m_currentAmmunition += nbAmmuition;
		if (m_currentAmmunition > MAX_AMMUNITION)
			m_currentAmmunition = MAX_AMMUNITION;
	}

	void Weapon::incAmmunitionExplosive(int nbAmmunition)
	{
		m_currentAmmunitionExplosive += nbAmmunition;
		if (m_currentAmmunitionExplosive > MAX_AMMUNITION_EXPLOSIVE)
			m_currentAmmunitionExplosive = MAX_AMMUNITION_EXPLOSIVE;
	}
};