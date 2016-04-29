#include "WeaponCreator.h"

WeaponCreator::WeaponCreator(const std::string& sXMLFilename):
	XML_FILENAME(sXMLFilename)
{

}

ecs::Weapon WeaponCreator::create(const ecs::Weapon::WeaponType eWeaponType)
{
	return m_lWeapons[eWeaponType];
}

void WeaponCreator::loadWeapons()
{

}

