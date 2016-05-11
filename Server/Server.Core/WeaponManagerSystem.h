#pragma once

// Server Version

#include "Entity.h"

namespace ecs
{
	class WeaponManagerSystem
	{
	public:
		WeaponManagerSystem() = delete;
		~WeaponManagerSystem() = delete;

		static void	changeToNext(Entity& player);
		static void changeToPrec(Entity& player);
	};

}