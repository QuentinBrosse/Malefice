#pragma once

#include "Entity.h"
#include "WeaponManager.h"
#include "Life.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT WeaponSystem
	{
	public:
		WeaponSystem() = delete;
		~WeaponSystem() = delete;
		static void	shoot(Entity& entity, bool isExplosive);
	};
}
