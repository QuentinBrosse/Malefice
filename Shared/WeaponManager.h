#pragma once

#include "AComponent.h"
#include "AWeapon.h"

namespace ecs
{
	class WeaponManager : public AComponent
	{
	public:
		WeaponManager(weapon::AWeapon *);
		~WeaponManager() = default;
		void			addWeapon(weapon::AWeapon * newWeapon);
		void			changeToNextWeapon();
		void			changeToPrecWeapon();
		weapon::AWeapon	*getCurrentWeapon() const;
		void			dump() const;
	private:
		std::vector<weapon::AWeapon *>	m_vWeapons;
		int								m_iCurrentWeapon;
	};
}