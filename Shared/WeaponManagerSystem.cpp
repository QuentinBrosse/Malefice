#include "WeaponManagerSystem.h"
#include "WeaponManager.h"

namespace ecs
{

	void WeaponManagerSystem::changeToNext(Entity& player)
	{
		WeaponManager*	weaponManager;

		if ((weaponManager = dynamic_cast<WeaponManager*>(player[WEAPON_MANAGER])) != nullptr)
			weaponManager->changeToNextWeapon();
	}

	void WeaponManagerSystem::changeToPrec(Entity& player)
	{
		WeaponManager*	weaponManager;

		if ((weaponManager = dynamic_cast<WeaponManager*>(player[WEAPON_MANAGER])) != nullptr)
			weaponManager->changeToPrecWeapon();
	}

}