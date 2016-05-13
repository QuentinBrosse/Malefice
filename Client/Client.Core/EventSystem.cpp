//Client version

#include "EventSystem.h"
#include "WeaponSystem.h"
#include "SpellSystem.h"
#include "GameEventReceiver.h"
#include "SpellManagerSystem.h"
#include "WeaponManagerSystem.h"

namespace ecs
{

	void	EventSystem::doEvents(Entity& localPlayer)
	{
		GameEventReceiver*					eventReceiver;

		if ((eventReceiver = dynamic_cast<GameEventReceiver*>(localPlayer[GAME_EVENT_RECEIVER])) != nullptr)
		{
			while (!eventReceiver->getEvents().empty())
			{
				switch (eventReceiver->getEvent())
				{
				case ecs::GameEventReceiver::LEFT_ATTACK:
					WeaponSystem::shoot(localPlayer, false);
					break;

				case ecs::GameEventReceiver::RIGHT_ATTACK:
					if (localPlayer.has(ComponentType::SPELL_MANAGER))
						SpellSystem::launchSpell(localPlayer);
					else
						WeaponSystem::shoot(localPlayer, true);
					break;

				case ecs::GameEventReceiver::NEXT_WEAPON:
					std::cout << "CHANGE TO NEXT WEAPON !" << std::endl;
					WeaponManagerSystem::changeToNext(localPlayer);
					break;

				case ecs::GameEventReceiver::PREC_WEAPON:
					std::cout << "CHANGE TO PREC WEAPON !" << std::endl;
					WeaponManagerSystem::changeToPrec(localPlayer);
					break;

				case ecs::GameEventReceiver::NEXT_SPELL:
					SpellManagerSystem::changeToNext(localPlayer);
					break;

				case ecs::GameEventReceiver::PREC_SPELL:
					SpellManagerSystem::changeToPrec(localPlayer);
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

}
