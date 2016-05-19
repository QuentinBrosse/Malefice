#include "WeaponCreator.h"
#include "Logger.h"

WeaponCreator::WeaponCreator()
{
	m_configurator = &WeaponsConfiguration::getInstance();
	m_weapons = m_configurator->getWeapons();
}

ecs::Weapon WeaponCreator::create(const ecs::Weapon::WeaponType weaponType)
{
	return m_weapons[weaponType];
}
