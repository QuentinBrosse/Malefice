#pragma once

//Client version

#include "Entity.h"

namespace ecs
{
	class EventSystem
	{
	public:
		EventSystem() = delete;
		~EventSystem() = delete;

		static void	doEvents(Entity& localPlayer);
	};
}