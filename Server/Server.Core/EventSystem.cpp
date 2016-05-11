//Server version

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
			;	//TODO: implement EventSystem
		}
	}

}
