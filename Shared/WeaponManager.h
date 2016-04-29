#pragma once

#include "Weapon.h"

namespace ecs
{
	class WeaponManager : public AComponent
	{
	public:
		WeaponManager(const Weapon& defaultWeapon);
		~WeaponManager() = default;

		void			addWeapon(const Weapon& newWeapon);
		void			changeToNextWeapon();
		void			changeToPrecWeapon();

		Weapon&			getCurrentWeapon() const;

		void			dump() const;
	private:
		std::map<Weapon::WeaponType, Weapon>			m_weapons;
		std::map<Weapon::WeaponType, Weapon>::iterator	m_currentWeapon;
	};
}