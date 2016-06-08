#include "LifeSystem.h"
#include "Life.h"
#include "Position.h"
#include "Weapon.h"
#include "WeaponManager.h"
#include "Team.h"
#include "ServerCore.h"
#include "PlayerInfos.h"

void	ecs::LifeSystem::die(ecs::Entity* dead)
{
	ecs::Life*			life = dynamic_cast<ecs::Life*>((*dead)[ecs::AComponent::ComponentType::LIFE]);
	ecs::Position*		position = dynamic_cast<ecs::Position*>((*dead)[ecs::AComponent::ComponentType::POSITION]);
	ecs::WeaponManager*	weaponManager = dynamic_cast<ecs::WeaponManager*>((*dead)[ecs::AComponent::ComponentType::WEAPON_MANAGER]);
	ecs::Team*			team = dynamic_cast<ecs::Team*>((*dead)[ecs::AComponent::ComponentType::TEAM]);

	LOG_DEBUG(GENERAL) << dynamic_cast<ecs::PlayerInfos *>((*dead)[ecs::AComponent::ComponentType::PLAYER_INFOS])->getNickname() << " is dead modafoka !";

	life->set(100);
/*	position->setVectorPosition(irr::core::vector3df(0, 0, 0));
	position->setVectorRotation(irr::core::vector3df(0, 0, 0));
	position->setVectorScale(irr::core::vector3df(1.0F, 1.0F, 1.0F));*/

	ServerCore::getInstance().getNetworkModule().callRPC(NetworkRPC::LIFE_SYSTEM_DIE,
		static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::LifeSystem),
		dead->getOwner(),
		false);

	if (weaponManager)
		weaponManager->reset();
	team->addDeath();
	// TODO: what about the scene?
	// TODO: if predator, what about the spells?
}
