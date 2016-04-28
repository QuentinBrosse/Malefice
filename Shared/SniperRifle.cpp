#include "SniperRifle.h"

namespace weapon
{
	SniperRifle::SniperRifle() : AWeapon("Sniper Rifle", 10, 5, 30, 50, true)
	{
	}

	void SniperRifle::shoot()
	{
		dump();
		std::cout << "I'm shooting" << std::endl;
	}
}