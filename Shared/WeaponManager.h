#pragma once

#include "Weapon.h"

namespace ecs
{
	class WeaponManager : public AComponent
	{
	public:
		WeaponManager(const Weapon &);
		~WeaponManager() = default;
		void			addWeapon(const Weapon &newWeapon);
		void			changeToNextWeapon();
		void			changeToPrecWeapon();
		const Weapon&	getCurrentWeapon() const;
		void			dump() const;
	private:
		std::vector<Weapon>		m_vWeapons;
		int						m_iCurrentWeapon;
	};
}