#pragma once

#include "Weapon.h"

namespace ecs
{
	class WeaponManager : public AComponent
	{
	public:
		WeaponManager(const Weapon& cDefaultWeapon);
		~WeaponManager() = default;
		void			addWeapon(const Weapon& cNewWeapon);
		void			changeToNextWeapon();
		void			changeToPrecWeapon();
		const Weapon&	getCurrentWeapon() const;
		void			dump() const;
	private:
		std::vector<Weapon>		m_lWeapons;
		std::vector<Weapon>::iterator	m_currentWeapon;
	};
}