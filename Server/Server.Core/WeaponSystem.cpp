#include "WeaponSystem.h"

namespace ecs
{
	void	WeaponSystem::shoot(Entity* entity, RakNet::RPC3* rpc)
	{
		WeaponManager*	weaponManager;

		if ((weaponManager = dynamic_cast<WeaponManager*>((*entity)[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr)
		{
			Weapon&	weapon = weaponManager->getCurrentWeapon();

			if (weapon.getAmmunitions() > 0)
				;//weapon.fired();
			else
				weapon.reload();
			//TODO: ray tracing etc..
		}
	}
}
