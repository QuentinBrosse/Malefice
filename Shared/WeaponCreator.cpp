#include "WeaponCreator.h"

WeaponCreator::WeaponCreator(const std::string& XMLFilename):
	XML_FILENAME(XMLFilename)
{
}

ecs::Weapon WeaponCreator::create(const ecs::Weapon::WeaponType weaponType)
{
	return m_weapons[weaponType];
}

void WeaponCreator::loadWeapons()
{

}

