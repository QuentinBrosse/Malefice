#pragma once

#include <string>
#include <map>
#include "Weapon.h"
#include "Export.h"
#include "WeaponsConfiguration.h"
#include "Singleton.h"

class MALEFICE_DLL_EXPORT WeaponCreator :  public Singleton<WeaponCreator>
{
	friend class Singleton<WeaponCreator>;

public:
	ecs::Weapon		create(const ecs::Weapon::WeaponType weaponType);

protected:
	WeaponCreator();
	virtual ~WeaponCreator() = default;

private:
	WeaponsConfiguration*							m_configurator;
	std::map<ecs::Weapon::WeaponType, ecs::Weapon>	m_weapons;

};
