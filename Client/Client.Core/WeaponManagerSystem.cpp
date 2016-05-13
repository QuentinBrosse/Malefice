// Client Version

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
			// TODO: send msg to server
		}
	}

	void WeaponManagerSystem::changeToPrec(Entity& player)
	{
		WeaponManager*	weaponManager;

		if ((weaponManager = dynamic_cast<WeaponManager*>(player[WEAPON_MANAGER])) != nullptr)
		{
			weaponManager->getCurrentWeapon().dump();
			weaponManager->changeToPrecWeapon();
			weaponManager->getCurrentWeapon().dump();
			// TODO: send msg to server
		}
	}

}