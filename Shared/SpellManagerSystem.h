#pragma once

#include "Entity.h"

namespace ecs
{

	class MALEFICE_DLL_EXPORT SpellManagerSystem
	{
	public:
		SpellManagerSystem() = delete;
		~SpellManagerSystem() = delete;

		static void	changeToNext(Entity& predator);
		static void	changeToPrec(Entity& predator);
	};

}