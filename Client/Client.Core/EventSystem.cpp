//Client version

#include "EventSystem.h"
#include "WeaponSystem.h"
#include "SpellSystem.h"
#include "SpellManagerSystem.h"
#include "WeaponManagerSystem.h"

namespace ecs
{

	void	EventSystem::doEvents(Entity& localPlayer)
	{
		GameEventReceiver*					eventReceiver;
		SpellManager*						spellManager;

		if ((eventReceiver = dynamic_cast<GameEventReceiver*>(localPlayer[ecs::AComponent::ComponentType::GAME_EVENT_RECEIVER])) != nullptr && (spellManager = dynamic_cast<SpellManager*>(localPlayer[ecs::AComponent::ComponentType::SPELL_MANAGER])) != nullptr)
			EventSystem::doPredatorEvents(localPlayer, eventReceiver, spellManager);
		else if (eventReceiver)
			EventSystem::doPlayerEvents(localPlayer, eventReceiver);
	}

	void EventSystem::doPredatorEvents(Entity& predator, GameEventReceiver* eventReceiver, SpellManager* spellManager)
	{
		while (!eventReceiver->getEvents().empty())
		{
			switch (eventReceiver->getEvent())
			{
			case ecs::GameEventReceiver::LEFT_ATTACK:
				WeaponSystem::shoot(predator, false);
				break;

			case ecs::GameEventReceiver::RIGHT_ATTACK:
				if (!spellManager->weaponsIsCurrent())
					SpellSystem::launchSpell(predator);
				else
					WeaponSystem::shoot(predator, true);
				break;

			case ecs::GameEventReceiver::NEXT_WEAPON:
				if (!spellManager->weaponsIsCurrent())
					SpellManagerSystem::changeToNext(predator);
				else
					WeaponManagerSystem::changeToNext(predator);
				break;

			case ecs::GameEventReceiver::PREC_WEAPON:
				if (!spellManager->weaponsIsCurrent())
					SpellManagerSystem::changeToPrec(predator);
				else
					WeaponManagerSystem::changeToPrec(predator);
				break;

			case ecs::GameEventReceiver::CHANGE_MANAGER:
				SpellManagerSystem::changeManager(predator);
				break;

			default:
				break;
			}
		}
	}

	void EventSystem::doPlayerEvents(Entity& localPlayer, GameEventReceiver* eventReceiver)
	{
		while (!eventReceiver->getEvents().empty())
		{
			switch (eventReceiver->getEvent())
			{
			case ecs::GameEventReceiver::LEFT_ATTACK:
				WeaponSystem::shoot(localPlayer, false);
				break;

			case ecs::GameEventReceiver::RIGHT_ATTACK:
				WeaponSystem::shoot(localPlayer, true);
				break;

			case ecs::GameEventReceiver::NEXT_WEAPON:
				WeaponManagerSystem::changeToNext(localPlayer);
				break;

			case ecs::GameEventReceiver::PREC_WEAPON:
				WeaponManagerSystem::changeToPrec(localPlayer);
				break;

			case ecs::GameEventReceiver::ZOOM:
				//TODO: Camera?
				break;
			default:
				break;
			}
		}
	}
}
