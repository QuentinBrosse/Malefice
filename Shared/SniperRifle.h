#pragma once

#include "AWeapon.h"

namespace weapon
{
	class SniperRifle : public AWeapon
	{
	public:
		SniperRifle();
		virtual ~SniperRifle() = default;
		void	shoot();
	private:
	};

}