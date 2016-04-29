#pragma once

#include "Weapon.h"

class WeaponCreator
{
public:
	WeaponCreator(const std::string& sXMLFilename);
	~WeaponCreator() = default;
	ecs::Weapon		create(const ecs::Weapon::WeaponType eWeaponType);
	void			loadWeapons();

private:
	std::map<ecs::Weapon::WeaponType, ecs::Weapon>	m_lWeapons;
	const std::string								XML_FILENAME;
};
