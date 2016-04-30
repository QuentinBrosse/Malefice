#pragma once

#include "Entity.h"
#include "Weapon.h"
#include "Life.h"

namespace ecs
{

	class WeaponSystem
	{
	public:
		WeaponSystem() = delete;
		~WeaponSystem() = delete;
		static void	shoot(Entity& entity, int nbAmmunition, bool isExplosive);
		static void	shootOnTarget(Entity& shooter, int nbAmmunition, bool isEplosive, Entity& target);
	};

}