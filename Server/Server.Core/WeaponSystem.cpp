<<<<<<< HEAD
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
							LOG_DEBUG(GENERAL) << dynamic_cast<ecs::PlayerInfos *>((*player.second)[ecs::AComponent::ComponentType::PLAYER_INFOS])->getNickname() << "is shoot modafoka !";
							break;
						}
					}
				}
			}

			//TODO: ray tracing etc..
		}
	}
}
=======
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
>>>>>>> 5e7d056b5b7081dd18f0a16498f3b1c16f88dcd9
