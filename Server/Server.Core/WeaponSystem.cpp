// SERVER VERSION

#include "WeaponSystem.h"
#include "PhysicsUtil.h"
#include "NodePickable.h"
#include "Armor.h"
#include "PlayerManager.h"
#include "ServerCore.h"
#include "PlayerInfos.h"
#include "LifeSystem.h"
#include "PositionSystem.h"
#include "Team.h"

namespace ecs
{
	void	WeaponSystem::shoot(Entity* entityClient, Line3dWrapper* rayWrap, RakNet::RPC3* rpc)
	{
		WeaponManager*	weaponManager;
		ecs::Entity*	entity = ServerCore::getInstance().getPlayerManager().findEntity(entityClient->getOwner());
		
		*entity = *entityClient;
		PositionSystem::updateScenePosition(*entity);
		ecs::SceneAnimatedMesh* scene = dynamic_cast<SceneAnimatedMesh*>((*entity)[ecs::AComponent::ComponentType::SCENE]);
		if ((weaponManager = dynamic_cast<WeaponManager*>((*entity)[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr)
		{
			Weapon&	weapon = weaponManager->getCurrentWeapon();
			PhysicsUtil& physicsUtil = PhysicsUtil::getInstance();
			PlayerManager& playerManager = ServerCore::getInstance().getPlayerManager();
			irr::core::line3df ray = rayWrap->getLine();
			if (weapon.shoot())
			{
				ServerCore::getInstance().getNetworkModule().callRPC(NetworkRPC::TRIGGER_SHOOT_ACTIONS, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::WeaponSystem), RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, entity); 
				irr::core::vector3df intersection;
				irr::core::triangle3df hitTriangle;
				irr::scene::ISceneNode* selectedSceneNode =
					physicsUtil.getSceneManager()->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(
						ray,
						intersection,
						hitTriangle,
						nodePickable::IS_PICKABLE,
						0);
  				if (selectedSceneNode && (selectedSceneNode->getID() & nodePickable::IS_SHOOTABLE) == nodePickable::IS_SHOOTABLE)
				{
					auto entities = playerManager.getEntities();
					for (auto& player : entities)
					{
						if (dynamic_cast<ecs::AScene *>((*player.second)[ecs::AComponent::ComponentType::SCENE])->getNode() == selectedSceneNode)
						{
							ecs::Life*	lifeTarget;
							ecs::Armor*	armorTarget;

							if ((armorTarget = dynamic_cast<ecs::Armor*>((*player.second)[ecs::AComponent::ComponentType::ARMOR])) != nullptr && (lifeTarget = dynamic_cast<ecs::Life*>((*player.second)[ecs::AComponent::ComponentType::LIFE])) != nullptr)
							{
								int rest = armorTarget->takeDamage(weapon.getDamage() * weapon.getAmmoPerShot());
								if (rest > 0)
								{
									rest = lifeTarget->takeDamage(rest);
									if (rest >= 0)
									{
										dynamic_cast<ecs::Team*>((*entity)[ecs::AComponent::ComponentType::TEAM])->addKill();
										LifeSystem::die(player.second);
									}
								}
							}
							break;
						}
					}
				}
			}
			else
				ServerCore::getInstance().getNetworkModule().callRPC(NetworkRPC::TRIGGER_SHOOT_ACTIONS, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::WeaponSystem), RakNet::UNASSIGNED_SYSTEM_ADDRESS, false, entity);
		}
	}
}
