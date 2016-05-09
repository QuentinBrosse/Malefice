#pragma once

#include "Entity.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT EventSystem
	{
	public:
		EventSystem() = delete;
		~EventSystem() = delete;

		static void	doEvents(Entity& localPlayer);
	};
}