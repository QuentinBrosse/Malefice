#pragma once

#include "Entity.h"
#include "WeaponManager.h"
#include "Life.h"

namespace ecs
{

	class WeaponSystem
	{
	public:
		WeaponSystem() = delete;
		~WeaponSystem() = delete;
		static void	shoot(Entity& entity, bool isExplosive);
	};

}