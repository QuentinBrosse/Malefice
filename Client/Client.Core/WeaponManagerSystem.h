#pragma once

// Client Version

#include "Entity.h"
#include "Export.h"
#include "ClientCore.h"

namespace ecs
{
	class WeaponManagerSystem
	{
	public:
		WeaponManagerSystem() = delete;
		~WeaponManagerSystem() = delete;

		static void	changeToNext(Entity& player);
		static void changeToPrec(Entity& player);
		static void initFPSWeapon(Entity& entity);
		static void initExternalWeapon(Entity& entity);
		static void	setCurrentWeaponVisibility(Entity& entity);
		static void reload(Entity& entity);
	};

}