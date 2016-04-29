#include "Weapon.h"

namespace ecs
{
	Weapon::Weapon(const std::string& name, const int maxAmmunition, const int maxAmmunitionExplosive, const int damage, const int damageExplosive, bool isGun) : AComponent("weapon", WEAPON),
		NAME(name), MAX_AMMUNITION(maxAmmunition), MAX_AMMUNITION_EXPLOSIVE(maxAmmunitionExplosive), DAMAGE(damage), DAMAGE_EXPLOSIVE(damageExplosive), IS_GUN(isGun)
	{
		m_iCurrentAmmunition = MAX_AMMUNITION;
		m_iCurrentAmmunitionExplosive = MAX_AMMUNITION_EXPLOSIVE;
	}

	Weapon::Weapon(const Weapon& cpy) : AComponent("weapon", WEAPON),
		NAME(cpy.NAME), MAX_AMMUNITION(cpy.MAX_AMMUNITION), MAX_AMMUNITION_EXPLOSIVE(cpy.MAX_AMMUNITION_EXPLOSIVE), DAMAGE(cpy.DAMAGE), DAMAGE_EXPLOSIVE(cpy.DAMAGE_EXPLOSIVE), IS_GUN(cpy.IS_GUN)
	{
		m_iCurrentAmmunition = cpy.m_iCurrentAmmunition;
		m_iCurrentAmmunitionExplosive = cpy.m_iCurrentAmmunitionExplosive;
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
};