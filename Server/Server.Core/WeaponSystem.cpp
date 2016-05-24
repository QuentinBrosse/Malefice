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
			/*
			 * TODO:
			 * 1) Get the entity we shot (let's call it "shotEntity")
			 * 2) If its life <= 0, call LifeSystem::die(shotEntity) (and LifeSystem::die itself call client's RPC die() or something)
			*/
		}
	}
}
