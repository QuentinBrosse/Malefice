#pragma once

#include <string>
#include <map>
#include <tinyxml2.h>
#include "AConfiguration.h"
#include "Weapon.h"
#include "Export.h"

class MALEFICE_DLL_EXPORT WeaponsConfiguration : public AConfiguration
{
public:
	static const std::string	WEAPONS_FILENAME;

	WeaponsConfiguration()			= default;
	virtual ~WeaponsConfiguration()	= default;

	virtual bool	loadFromFile(const std::string& filepath);
	virtual bool	saveToFile(const std::string& filepath)	const;


	const std::map<ecs::Weapon::WeaponType, ecs::Weapon>	&getWeapons()	const;


private:
	ecs::Weapon::WeaponType	parseWeaponType(const std::string& weaponTypeStr)	const;

	std::map<ecs::Weapon::WeaponType, ecs::Weapon>	m_weapons;
};
