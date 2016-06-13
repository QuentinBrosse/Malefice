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
#include "SpellManager.h"

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
							ecs::Team*	teamShooter;
							ecs::Team*	teamTarget;

							if ((teamShooter = dynamic_cast<ecs::Team*>((*entity)[ecs::AComponent::ComponentType::TEAM])) != nullptr
								&& (teamTarget = dynamic_cast<ecs::Team*>((*player.second)[ecs::AComponent::ComponentType::TEAM])) != nullptr
								&& teamShooter->getTeam() != teamTarget->getTeam()
								&& (armorTarget = dynamic_cast<ecs::Armor*>((*player.second)[ecs::AComponent::ComponentType::ARMOR])) != nullptr
								&& (lifeTarget = dynamic_cast<ecs::Life*>((*player.second)[ecs::AComponent::ComponentType::LIFE])) != nullptr)
							{
								ServerCore::getInstance().getNetworkModule().callRPC(NetworkRPC::TRIGGER_SHOOT_ACTIONS, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::WeaponSystem), RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, entity, 0, player.second->getOwner());
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
			else if (weapon.getAmmunitionsClip() > 0)
				ServerCore::getInstance().getNetworkModule().callRPC(NetworkRPC::TRIGGER_SHOOT_ACTIONS, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::WeaponSystem), RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, entity, 1, -1);
			else
				ServerCore::getInstance().getNetworkModule().callRPC(NetworkRPC::TRIGGER_SHOOT_ACTIONS, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::WeaponSystem), RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, entity, 2 , -1);
		}
	}

	void WeaponSystem::reload(Entity* entityClient, RakNet::RPC3* rpc)
	{
		WeaponManager*	weaponManager;
		SpellManager*	spellManager;
		ecs::Entity*	entity = ServerCore::getInstance().getPlayerManager().findEntity(entityClient->getOwner());

		*entity = *entityClient;
		if ((weaponManager = dynamic_cast<WeaponManager*>((*entity)[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr && weaponManager->hasCurrentWeapon())
			weaponManager->getCurrentWeapon().reload();
		else if ((spellManager = dynamic_cast<SpellManager*>((*entity)[ecs::AComponent::ComponentType::SPELL_MANAGER])) != nullptr && spellManager->hasCurrentWeapon())
			spellManager->getCurrentWeapon().reload();

	}
}
