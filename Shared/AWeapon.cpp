#include "AWeapon.h"

namespace ecs
{
	AWeapon::AWeapon(const std::string &name, const int maxAmmunition, const int maxAmmunitionExplosive, const int damage, const int damageExplosive) : AComponent("Weapon", WEAPON),
		NAME(name), MAX_AMMUNITION(maxAmmunition), MAX_AMMUNITION_EXPLOSIVE(maxAmmunitionExplosive), DAMAGE(damage), DAMAGE_EXPLOSIVE(damageExplosive)
	{
		m_iCurrentAmmunition = MAX_AMMUNITION;
		m_iCurrentAmmunitionExplosive = MAX_AMMUNITION_EXPLOSIVE;
	}

	AWeapon::~AWeapon()
	{

	}

	void	AWeapon::dump() const
	{
		std::cout << "[" << NAME << "/" << m_iCurrentAmmunition << "/" << MAX_AMMUNITION << "/" << m_iCurrentAmmunitionExplosive << "/" << MAX_AMMUNITION_EXPLOSIVE << "/" << DAMAGE << "/" << DAMAGE_EXPLOSIVE <<"]" << std::endl;
	}

	int		AWeapon::getDamage() const
	{
		return (DAMAGE);
	}

	int		AWeapon::getDamageExplosive() const
	{
		return (DAMAGE_EXPLOSIVE);
	}

	int			AWeapon::getAmmunition() const
	{
		return (m_iCurrentAmmunition);
	}

	int			AWeapon::getAmmunitionExplosive() const
	{
		return (m_iCurrentAmmunitionExplosive);
	}
};