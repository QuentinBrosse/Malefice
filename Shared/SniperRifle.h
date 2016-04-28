#pragma once

#include "AWeapon.h"

namespace weapon
{
	class SniperRifle : public ecs::AWeapon
	{
	public:
		SniperRifle();
		virtual ~SniperRifle() = default;
		void	shoot();
	private:
	};

}