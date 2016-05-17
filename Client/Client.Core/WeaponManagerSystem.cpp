// Client Version

#include "WeaponManagerSystem.h"
#include "WeaponManager.h"

namespace ecs
{

	void WeaponManagerSystem::changeToNext(Entity& player)
	{
		WeaponManager*	weaponManager;

		if ((weaponManager = dynamic_cast<WeaponManager*>(player[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr)
		{
			weaponManager->changeToNextWeapon();
			// TODO: send msg to server
		}
	}

	void WeaponManagerSystem::changeToPrec(Entity& player)
	{
		WeaponManager*	weaponManager;

		if ((weaponManager = dynamic_cast<WeaponManager*>(player[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr)
		{
			weaponManager->changeToPrecWeapon();
			// TODO: send msg to server
		}
	}

}