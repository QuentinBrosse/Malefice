#include "Weapon.h"

namespace ecs
{
	Weapon::Weapon() : AComponent("Weapon", WEAPON),
		WEAPON_NAME("Weapon"), MAX_AMMUNITION(0), MAX_AMMUNITION_EXPLOSIVE(0), DAMAGE(0), DAMAGE_EXPLOSIVE(0), WEAPON_TYPE(DEFAULT), IS_GUN(false)
	{
		m_iCurrentAmmunition = MAX_AMMUNITION;
		m_iCurrentAmmunitionExplosive = MAX_AMMUNITION_EXPLOSIVE;
	}

	Weapon::Weapon(const std::string& sName, const int iMaxAmmunition, const int iMaxAmmunitionExplosive, const int iDamage, const int iDamageExplosive, const WeaponType eWeaponType, const bool bIsGun) : AComponent("Weapon", WEAPON),
		WEAPON_NAME(sName), MAX_AMMUNITION(iMaxAmmunition), MAX_AMMUNITION_EXPLOSIVE(iMaxAmmunitionExplosive), DAMAGE(iDamage), DAMAGE_EXPLOSIVE(iDamageExplosive), WEAPON_TYPE(eWeaponType), IS_GUN(bIsGun)
	{
		m_iCurrentAmmunition = MAX_AMMUNITION;
		m_iCurrentAmmunitionExplosive = MAX_AMMUNITION_EXPLOSIVE;
	}

	Weapon::Weapon(const Weapon& cpy) : AComponent("Weapon", WEAPON),
		WEAPON_NAME(cpy.NAME), MAX_AMMUNITION(cpy.MAX_AMMUNITION), MAX_AMMUNITION_EXPLOSIVE(cpy.MAX_AMMUNITION_EXPLOSIVE), DAMAGE(cpy.DAMAGE), DAMAGE_EXPLOSIVE(cpy.DAMAGE_EXPLOSIVE), WEAPON_TYPE(cpy.WEAPON_TYPE), IS_GUN(cpy.IS_GUN)
	{
		m_iCurrentAmmunition = cpy.m_iCurrentAmmunition;
		m_iCurrentAmmunitionExplosive = cpy.m_iCurrentAmmunitionExplosive;
	}

	Weapon& Weapon::operator=(const Weapon& other)
	{
		m_iCurrentAmmunition = other.m_iCurrentAmmunition;
		m_iCurrentAmmunitionExplosive = other.m_iCurrentAmmunitionExplosive;
		return *this;
	}

	void	Weapon::dump() const
	{
		std::cout << "[" << NAME << "/" << m_iCurrentAmmunition << "/" << MAX_AMMUNITION << "/" << m_iCurrentAmmunitionExplosive << "/" << MAX_AMMUNITION_EXPLOSIVE << "/" << DAMAGE << "/" << DAMAGE_EXPLOSIVE <<"]" << std::endl;
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
		return m_iCurrentAmmunition;
	}

	int			Weapon::getAmmunitionExplosive() const
	{
		return m_iCurrentAmmunitionExplosive;
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