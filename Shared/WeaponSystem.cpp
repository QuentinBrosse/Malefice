#include "WeaponSystem.h"

namespace ecs
{
	void WeaponSystem::shoot(Entity& entity, int nbAmmunition, bool isExplosive)
	{
		Weapon*	weapon;

		if ((weapon = dynamic_cast<Weapon*>(entity[WEAPON])) != nullptr)
		{
			if (isExplosive)
				weapon->decAmmunitionExplosive(nbAmmunition);
			else
				weapon->decAmmunition(nbAmmunition);
		}
	}

	void WeaponSystem::shootOnTarget(Entity & shooter, int nbAmmunition, bool isExplosive, Entity & target)
	{
		Weapon	*weaponOfShooter;
		Life	*lifeOfTarget;

		if ((weaponOfShooter = dynamic_cast<Weapon*>(shooter[WEAPON])) != nullptr && (lifeOfTarget = dynamic_cast<Life*>(target[LIFE])) != nullptr)
		{
			if (isExplosive)
			{
				lifeOfTarget->takeDamage(weaponOfShooter->getDamageExplosive());
				weaponOfShooter->decAmmunitionExplosive(nbAmmunition);
			}
			else
			{
				lifeOfTarget->takeDamage(weaponOfShooter->getDamage());
				weaponOfShooter->decAmmunition(nbAmmunition);
			}

		}
		else if (weaponOfShooter)
		{
			if (isExplosive)
				weaponOfShooter->decAmmunitionExplosive(nbAmmunition);
			else
				weaponOfShooter->decAmmunition(nbAmmunition);
		}
	}

}
