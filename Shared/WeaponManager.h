#pragma once

#include <map>
#include <BitStream.h>
#include "Weapon.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT WeaponManager : public AComponent
	{
	public:
		WeaponManager();
		WeaponManager(const WeaponManager& cpy);
		WeaponManager(Weapon& defaultWeapon);
		~WeaponManager()	= default;

		virtual void	init(Weapon& defaultWeapon);
		void			reset();

		void			addWeapon(const Weapon& newWeapon);
		void			changeToNextWeapon();
		void			changeToPrecWeapon();

		bool			hasCurrentWeapon() const;
		Weapon&									getCurrentWeapon()	const;
		std::map<Weapon::WeaponType, Weapon>&	getWeapons();

		void				createWeapon(irr::IrrlichtDevice* device, const Weapon& weaponCpy);
			

		virtual	void		dump(std::ostream& os)	const;

		virtual AComponent&	affect(const AComponent& rhs);

		virtual void		serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void		deserialize(RakNet::BitStream& in);

		virtual AComponent*	createCopy(const AComponent* rhs) const;

	private:
		std::map<Weapon::WeaponType, Weapon>			m_weapons;
		std::map<Weapon::WeaponType, Weapon>::iterator	m_currentWeapon;
	};
}
