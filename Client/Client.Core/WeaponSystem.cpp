// Client Version

#include "WeaponSystem.h"
#include "SceneAnimatedMesh.h"

namespace ecs
{
	void				WeaponSystem::shoot(Entity& entity, bool isExplosive)
	{
		WeaponManager*	weaponManager;

		if ((weaponManager = dynamic_cast<WeaponManager*>(entity[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr)
		{
			Weapon&	weapon = weaponManager->getCurrentWeapon();

			if (weapon.getAmmunitions() > 0)
				weapon.shot();
			else
				weapon.reload();

			//TODO: sens to msg to server
		}
	}

}
