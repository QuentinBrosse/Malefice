#include "WeaponCreator.h"


WeaponCreator::WeaponCreator():
	m_weaponConfigurator()
{
	
}

ecs::Weapon WeaponCreator::create(const ecs::Weapon::WeaponType weaponType)
{
	std::map<ecs::Weapon::WeaponType, ecs::Weapon>	weapons;

	weapons = m_weaponConfigurator.getWeapons();

	return weapons[weaponType];
}
