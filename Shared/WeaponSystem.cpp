#include "WeaponSystem.h"

namespace ecs
{
	void				WeaponSystem::shoot(Entity& entity, int nbAmmunition, bool isExplosive)
	{
		WeaponManager*	weaponManager;

		if ((weaponManager = dynamic_cast<WeaponManager*>(entity[WEAPON_MANAGER])) != nullptr)
		{
			Weapon&	weapon = weaponManager->getCurrentWeapon();
			if (isExplosive)
				weapon.decAmmunitionExplosive(nbAmmunition);
			else
				weapon.decAmmunition(nbAmmunition);
		}
	}

	void				WeaponSystem::shootOnTarget(Entity& shooter, int nbAmmunition, bool isExplosive, Entity& target)
	{
		WeaponManager*	weaponManager;
		Life*			lifeOfTarget;

		if ((weaponManager = dynamic_cast<WeaponManager*>(shooter[WEAPON_MANAGER])) != nullptr && (lifeOfTarget = dynamic_cast<Life*>(target[LIFE])) != nullptr)
		{
			Weapon&	weaponOfShooter = weaponManager->getCurrentWeapon();
			if (isExplosive)
			{
				lifeOfTarget->takeDamage(weaponOfShooter.getDamageExplosive());
				weaponOfShooter.decAmmunitionExplosive(nbAmmunition);
			}
			else
			{
				lifeOfTarget->takeDamage(weaponOfShooter.getDamage());
				weaponOfShooter.decAmmunition(nbAmmunition);
			}

		}
		else if (weaponManager)
		{
			Weapon&	weaponOfShooter = weaponManager->getCurrentWeapon();
			if (isExplosive)
				weaponOfShooter.decAmmunitionExplosive(nbAmmunition);
			else
				weaponOfShooter.decAmmunition(nbAmmunition);
		}
	}

}
