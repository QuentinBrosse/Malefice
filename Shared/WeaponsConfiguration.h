#pragma once

#include <string>
#include <map>
#include <tinyxml2.h>
#include "AConfiguration.h"
#include "Weapon.h"
#include "Export.h"
#include "Singleton.h"

class MALEFICE_DLL_EXPORT WeaponsConfiguration : public AConfiguration, public Singleton<WeaponsConfiguration>
{
	friend class Singleton<WeaponsConfiguration>;

protected:
	WeaponsConfiguration();
	virtual ~WeaponsConfiguration() = default;

public:
	virtual bool											saveToFile(const std::string& filepath) const;
	virtual bool											loadFromFile(const std::string& filepath);
	const std::map<ecs::Weapon::WeaponType, ecs::Weapon>&	getWeapons() const;

private:
	static const std::string								WEAPONS_FILENAME;
	std::map<ecs::Weapon::WeaponType, ecs::Weapon>			m_weapons;
	ecs::Weapon::WeaponType									parseWeaponType(const std::string& weaponTypeStr) const;
};
