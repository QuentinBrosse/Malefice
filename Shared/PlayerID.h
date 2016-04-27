#pragma once

#include "AComponent.h"

namespace ecs
{
	class PlayerID: public AComponent
	{
	public:
		PlayerID(int id);
		~PlayerID() = default;

		void dump() const;

	public:
		const int ID;
	};

}