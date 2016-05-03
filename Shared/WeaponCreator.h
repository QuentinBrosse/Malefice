#pragma once

#include <string>
#include <map>
#include "Weapon.h"
#include "Export.h"

class MALEFICE_DLL_EXPORT WeaponCreator
{
public:
	WeaponCreator(const std::string& XMLFilename);
	~WeaponCreator()	= default;

	ecs::Weapon		create(const ecs::Weapon::WeaponType weaponType);
	void			loadWeapons();


private:
	std::map<ecs::Weapon::WeaponType, ecs::Weapon>	m_weapons;
	const std::string								XML_FILENAME;
};
