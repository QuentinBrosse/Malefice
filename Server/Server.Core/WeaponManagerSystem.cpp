// Server Version

#include "WeaponManagerSystem.h"
#include "WeaponManager.h"

namespace ecs
{

	void WeaponManagerSystem::changeToNext(Entity& player)
	{
		WeaponManager*	weaponManager;

		if ((weaponManager = dynamic_cast<WeaponManager*>(player[WEAPON_MANAGER])) != nullptr)
		{
			weaponManager->changeToNextWeapon();
			//TODO: update?
		}
	}

	void WeaponManagerSystem::changeToPrec(Entity& player)
	{
		WeaponManager*	weaponManager;

		if ((weaponManager = dynamic_cast<WeaponManager*>(player[WEAPON_MANAGER])) != nullptr)
		{
			//TODO: update?
			weaponManager->changeToPrecWeapon();
		}
	}

}