// SERVER VERSION

#include "SpellSystem.h"
#include "SpellManager.h"
#include "Spell.h"
#include "PhysicsUtil.h"
#include "PlayerManager.h"
#include "ServerCore.h"
#include "NodePickable.h"
#include "PlayerInfos.h"
#include "PositionSystem.h"
#include "TimeUtility.h"

namespace ecs
{
	void SpellSystem::launchSpell(Entity* predatorClient, Line3dWrapper* rayWrap, RakNet::RPC3* rpc)
	{
		SpellManager*	spellManager;
		ecs::Entity*	predator = ServerCore::getInstance().getPlayerManager().findEntity(predatorClient->getOwner());

		*predator = *predatorClient;
		PositionSystem::updateScenePosition(*predator);
		if ((spellManager = dynamic_cast<SpellManager*>((*predator)[ecs::AComponent::ComponentType::SPELL_MANAGER])) != nullptr)
		{
			Spell&	spellOfPredator = spellManager->getCurrentSpell();
			
			PhysicsUtil& physicsUtil = PhysicsUtil::getInstance();
			PlayerManager& playerManager = ServerCore::getInstance().getPlayerManager();
			irr::core::line3df	ray = rayWrap->getLine();
			if (!spellOfPredator.isLock())
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

				const auto& entities = playerManager.getEntities();

				if (selectedSceneNode != nullptr && (selectedSceneNode->getID() & nodePickable::IS_SHOOTABLE) == nodePickable::IS_SHOOTABLE)
				{
					for (auto& player : entities)
					{
						if (dynamic_cast<ecs::AScene *>((*player.second)[ecs::AComponent::ComponentType::SCENE])->getNode() == selectedSceneNode)
						{
							Spell*	spellOfTarget;

							LOG_DEBUG(GENERAL) << dynamic_cast<ecs::PlayerInfos*>((*player.second)[ecs::AComponent::ComponentType::PLAYER_INFOS])->getNickname() << " is shot WITH SPELL modafoka !";
							if ((spellOfTarget = dynamic_cast<Spell*>((*player.second)[ecs::AComponent::ComponentType::SPELL])) != nullptr
								&& !spellOfTarget->isLock()
								&& spellOfTarget->getSpellType() == Spell::SpellType::NOTHING)
							{
								long long	spellEffectEndTime = utility::TimeUtility::getMsTime() + spellOfPredator.getDuration() * 1000;
								long long	spellCooldownEndTime = utility::TimeUtility::getMsTime() + spellOfPredator.getCooldown() * 1000;

								spellOfTarget->setSpellType(spellOfPredator.getSpellType());

								spellOfTarget->setEffectEndTime(spellEffectEndTime);
								spellOfTarget->setCooldownEndTime(spellCooldownEndTime);
							}
							break;
						}
					}
				}
			}
		}
	}

	void SpellSystem::checkSpell(Entity& entity)
	{
		Spell*			spell;
		SpellManager*	spellManager;

		if ((spell = dynamic_cast<Spell*>(entity[ecs::AComponent::ComponentType::SPELL])) != nullptr)
		{
			if (spell->getSpellType() != Spell::SpellType::NOTHING)
			{
				if (utility::TimeUtility::getMsTime() >= spell->getEffectEndTime())
				{
					spell->setSpellType(ecs::Spell::SpellType::NOTHING);
				}
			}
		}
	}
}
