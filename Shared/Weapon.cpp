#include <iostream>
#include "Weapon.h"

namespace ecs
{
	Weapon::Weapon() : AComponent("Weapon", WEAPON),
		WEAPON_NAME("Weapon"), MAX_AMMUNITION(0), MAX_AMMUNITION_EXPLOSIVE(0), DAMAGE(0), DAMAGE_EXPLOSIVE(0), WEAPON_TYPE(DEFAULT), IS_GUN(false)
	{
		m_currentAmmunition = MAX_AMMUNITION;
		m_currentAmmunitionExplosive = MAX_AMMUNITION_EXPLOSIVE;
	}

	Weapon::Weapon(const std::string& name, const int maxAmmunition, const int maxAmmunitionExplosive, const int damage, const int damageExplosive, const WeaponType weaponType, const bool isGun) : AComponent("Weapon", WEAPON),
		WEAPON_NAME(name), MAX_AMMUNITION(maxAmmunition), MAX_AMMUNITION_EXPLOSIVE(maxAmmunitionExplosive), DAMAGE(damage), DAMAGE_EXPLOSIVE(damageExplosive), WEAPON_TYPE(weaponType), IS_GUN(isGun)
	{
		m_currentAmmunition = MAX_AMMUNITION;
		m_currentAmmunitionExplosive = MAX_AMMUNITION_EXPLOSIVE;
	}

	Weapon::Weapon(const Weapon& cpy) : AComponent("Weapon", WEAPON),
		WEAPON_NAME(cpy.NAME), MAX_AMMUNITION(cpy.MAX_AMMUNITION), MAX_AMMUNITION_EXPLOSIVE(cpy.MAX_AMMUNITION_EXPLOSIVE), DAMAGE(cpy.DAMAGE), DAMAGE_EXPLOSIVE(cpy.DAMAGE_EXPLOSIVE), WEAPON_TYPE(cpy.WEAPON_TYPE), IS_GUN(cpy.IS_GUN)
	{
		m_currentAmmunition = cpy.m_currentAmmunition;
		m_currentAmmunitionExplosive = cpy.m_currentAmmunitionExplosive;
	}

	Weapon& Weapon::operator=(const Weapon& other)
	{
		m_currentAmmunition = other.m_currentAmmunition;
		m_currentAmmunitionExplosive = other.m_currentAmmunitionExplosive;
		return *this;
	}

	void	Weapon::dump() const
	{
		std::cout << "[" << NAME << "/" << m_currentAmmunition << "/" << MAX_AMMUNITION << "/" << m_currentAmmunitionExplosive << "/" << MAX_AMMUNITION_EXPLOSIVE << "/" << DAMAGE << "/" << DAMAGE_EXPLOSIVE <<"]" << std::endl;
	}

	int		Weapon::getDamage() const
	{
		return DAMAGE;
	}

	int		Weapon::getDamageExplosive() const
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
};