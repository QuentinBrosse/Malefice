#include "WeaponSystem.h"

namespace ecs
{
	void	WeaponSystem::shoot(Entity* entity, irr::core::line3df* ray, RakNet::RPC3* rpc)
	{
		WeaponManager*	weaponManager;

		if ((weaponManager = dynamic_cast<WeaponManager*>((*entity)[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr)
		{
			Weapon&	weapon = weaponManager->getCurrentWeapon();

			weapon.shoot();

			//TODO: ray tracing etc..
		}
	}
}
