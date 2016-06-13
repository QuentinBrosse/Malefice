// Server Version

#include "WeaponManagerSystem.h"
#include "WeaponManager.h"

namespace ecs
{

	void WeaponManagerSystem::changeWeapon(Entity* playerClient, RakNet::RPC3* rpc)
	{
		ecs::Entity*		entity = ServerCore::getInstance().getPlayerManager().findEntity(playerClient->getOwner());
		ecs::WeaponManager*	weaponManagerLocal;
		ecs::WeaponManager*	weaponManagerClient;

		if ((weaponManagerLocal = dynamic_cast<ecs::WeaponManager*>((*entity)[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr
			&& (weaponManagerClient = dynamic_cast<ecs::WeaponManager*>((*playerClient)[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr)
		{
			weaponManagerLocal->affect(*weaponManagerClient);
		}

	}
}