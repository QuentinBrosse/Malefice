//Client version

#include "EventSystem.h"
#include "WeaponSystem.h"
#include "SpellSystem.h"
#include "SpellManagerSystem.h"
#include "WeaponManagerSystem.h"
#include "GraphicUtil.h"

namespace ecs
{

	void	EventSystem::doEvents(Entity& localPlayer)
	{
		EventReceiver&						eventReceiver = GraphicUtil::getInstance().getCEGUIEventReceiver();
		SpellManager*						spellManager;

		if ((spellManager = dynamic_cast<SpellManager*>(localPlayer[ecs::AComponent::ComponentType::SPELL_MANAGER])) != nullptr)
			EventSystem::doPredatorEvents(localPlayer, eventReceiver, spellManager); 
		else
			EventSystem::doPlayerEvents(localPlayer, eventReceiver);
	}

	void EventSystem::doPredatorEvents(Entity& predator, EventReceiver& eventReceiver, SpellManager* spellManager)
	{
		while (!eventReceiver.getEvents().empty())
		{
			switch (eventReceiver.getEvent())
			{
			case EventReceiver::GameEventType::LEFT_ATTACK:
				if (!spellManager->weaponsIsCurrent())
					SpellSystem::launchSpell(predator);
				else
					WeaponSystem::shoot(predator);
				break;				

			case EventReceiver::NEXT_WEAPON:
				if (!spellManager->weaponsIsCurrent())
					SpellManagerSystem::changeToNext(predator);
				else
					WeaponManagerSystem::changeToNext(predator);
				break;

			case EventReceiver::PREC_WEAPON:
				if (!spellManager->weaponsIsCurrent())
					SpellManagerSystem::changeToPrec(predator);
				else
					WeaponManagerSystem::changeToPrec(predator);
				break;

			case EventReceiver::CHANGE_MANAGER:
				SpellManagerSystem::changeManager(predator);
				break;

			default:
				break;
			}
		}
	}

	void EventSystem::doPlayerEvents(Entity& localPlayer, EventReceiver& eventReceiver)
	{
		while (!eventReceiver.getEvents().empty())
		{
			switch (eventReceiver.getEvent())
			{
			case EventReceiver::LEFT_ATTACK:
				WeaponSystem::shoot(localPlayer);
				break;

			case EventReceiver::NEXT_WEAPON:
				WeaponManagerSystem::changeToNext(localPlayer);
				break;

			case EventReceiver::PREC_WEAPON:
				WeaponManagerSystem::changeToPrec(localPlayer);
				break;

			case EventReceiver::ZOOM:
				//TODO: Camera?
				break;
			default:
				break;
			}
		}
	}
}
