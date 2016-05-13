#pragma once

#include "Life.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT Armor: public Life
	{
	public:
		Armor(int maxHP);
		~Armor() = default;
	};

}