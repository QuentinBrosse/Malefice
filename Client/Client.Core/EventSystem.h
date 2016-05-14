#pragma once

//Client version

#include "Entity.h"
#include "SpellManager.h"
#include "GameEventReceiver.h"

namespace ecs
{
	class EventSystem
	{
	public:
		EventSystem() = delete;
		~EventSystem() = delete;

		static void	doEvents(Entity& localPlayer);
		static void	doPredatorEvents(Entity& predator, GameEventReceiver* eventReceiver, SpellManager* spellManager);
		static void	doPlayerEvents(Entity& localPlayer, GameEventReceiver* eventReceiver);
	};
}