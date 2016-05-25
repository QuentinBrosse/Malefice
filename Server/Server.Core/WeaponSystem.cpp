#include "WeaponSystem.h"
#include "PhysicsUtil.h"
#include "NodePickable.h"
#include "PlayerManager.h"
#include "ServerCore.h"
#include "PlayerInfos.h"

namespace ecs
{
	void	WeaponSystem::shoot(Entity* entity, RakNet::RPC3* rpc)
	{
		WeaponManager*	weaponManager;


		if ((weaponManager = dynamic_cast<WeaponManager*>((*entity)[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr)
		{
			Weapon&	weapon = weaponManager->getCurrentWeapon();
			PhysicsUtil& physicsUtil = PhysicsUtil::getInstance();
			PlayerManager& playerManager = ServerCore::getInstance().getPlayerManager();
			irr::core::line3df	ray = weapon.getRay();

			if (weapon.shoot())
			{
				irr::core::vector3df intersection;
				irr::core::triangle3df hitTriangle;
				irr::scene::ISceneNode* selectedSceneNode =
					physicsUtil.getSceneManager()->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(
						ray,
						intersection,
						hitTriangle,
						nodePickable::IS_PICKABLE,
						0);

				auto entities = playerManager.getEntities();

				if (selectedSceneNode && (selectedSceneNode->getID() & nodePickable::IS_SHOOTABLE) == nodePickable::IS_SHOOTABLE)
				{
					for (auto player : entities)
					{
						if (dynamic_cast<ecs::AScene *>((*player.second)[ecs::AComponent::ComponentType::SCENE])->getNode() == selectedSceneNode)
						{
							LOG_DEBUG(GENERAL) << dynamic_cast<ecs::PlayerInfos *>((*player.second)[ecs::AComponent::ComponentType::PLAYER_INFOS])->getNickname() << " is shot modafoka !";
							break;
						}
					}
				}
			}
		}
	}
}