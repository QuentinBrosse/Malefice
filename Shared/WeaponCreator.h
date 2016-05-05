#pragma once

#include <string>
#include <map>
#include "Weapon.h"
#include "Export.h"
#include "WeaponsConfiguration.h"
#include "Singleton.h"

class MALEFICE_DLL_EXPORT WeaponCreator :  public Singleton<WeaponCreator>
{

public:
	ecs::Weapon		create(const ecs::Weapon::WeaponType weaponType);
	~WeaponCreator() = default;
	WeaponCreator();

private:
	WeaponsConfiguration	m_weaponConfigurator;
};
