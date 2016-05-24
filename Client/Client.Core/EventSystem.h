#pragma once

//Client version

#include "Entity.h"
#include "SpellManager.h"
#include "EventReceiver.h"

namespace ecs
{
	class EventSystem
	{
	public:
		EventSystem() = delete;
		~EventSystem() = delete;

		static void	doEvents(Entity& localPlayer);
		static void	doPredatorEvents(Entity& predator, EventReceiver& eventReceiver, SpellManager* spellManager);
		static void	doPlayerEvents(Entity& localPlayer, EventReceiver& eventReceiver);
	};
}