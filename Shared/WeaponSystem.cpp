#include "WeaponSystem.h"

namespace ecs
{
	void				WeaponSystem::shoot(Entity& entity, bool isExplosive)
	{
		WeaponManager*	weaponManager;

		if ((weaponManager = dynamic_cast<WeaponManager*>(entity[WEAPON_MANAGER])) != nullptr)
		{
			Weapon&	weapon = weaponManager->getCurrentWeapon();
			if (isExplosive)
			{
				if (weapon.getAmmunitionExplosiveLoader() > 0)
					weapon.firedExplosive();
				else
					weapon.reloadExplosive();
			}
			else
			{
				if (weapon.getAmmunitionLoader() > 0)
					weapon.fired();
				else
					weapon.reload();
			}
		}
	}

}
