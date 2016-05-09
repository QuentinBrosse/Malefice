#pragma once

#include "Export.h"

namespace ecs
{
	enum MALEFICE_DLL_EXPORT ComponentType
	{
		DEFAULT,
		LIFE,
		POSITION,
		MOVEMENT,
		TEAM,
		WEAPON,
		WEAPON_MANAGER,
		SPELL,
		SPELL_MANAGER,
		GAME_EVENT_RECEIVER,
	};
}
