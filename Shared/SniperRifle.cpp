#include "SniperRifle.h"

namespace weapon
{
	SniperRifle::SniperRifle() : AWeapon("SniperRifle", 10, 5, 30, 50, true)
	{
	}

	void SniperRifle::shoot()
	{
		dump();
		std::cout << "I'm shooting" << std::endl;
	}
}