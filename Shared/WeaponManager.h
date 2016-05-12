#pragma once

#include <map>
#include "Weapon.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT WeaponManager : public AComponent
	{
	public:
		WeaponManager(const Weapon& defaultWeapon);
		~WeaponManager()	= default;

		void			addWeapon(const Weapon& newWeapon);
		void			changeToNextWeapon();
		void			changeToPrecWeapon();

		Weapon&			getCurrentWeapon()	const;


		virtual void	dump(std::ostream& os)	const;


	private:
		std::map<Weapon::WeaponType, Weapon>			m_weapons;
		std::map<Weapon::WeaponType, Weapon>::iterator	m_currentWeapon;
	};
}
