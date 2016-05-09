#pragma once

#include "Entity.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT WeaponManagerSystem
	{
	public:
		WeaponManagerSystem() = delete;
		~WeaponManagerSystem() = delete;

		static void	changeToNext(Entity& player);
		static void changeToPrec(Entity& player);
	};

}