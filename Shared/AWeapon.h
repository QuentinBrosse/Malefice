#pragma once

#include "StdInc.h"

namespace weapon
{
	class AWeapon
	{
	public:
		AWeapon(const std::string &name, int maxAmmunition, const int maxAmmunitionExplosive, const int damage, const int damageExplosive, bool isGun);
		virtual ~AWeapon() = default;
		virtual void	shoot() = 0;
		virtual void	dump() const;
		int				getDamage() const;
		int				getDamageExplosive() const;
		int				getAmmunition() const;
		int				getAmmunitionExplosive() const;
		bool			isGun() const;
	private:
		const std::string	NAME;
		const int			MAX_AMMUNITION;
		const int			MAX_AMMUNITION_EXPLOSIVE;
		const int			DAMAGE;
		const int			DAMAGE_EXPLOSIVE;
		int					m_iCurrentAmmunition;
		int					m_iCurrentAmmunitionExplosive;
		bool				m_bIsGun;
	};


}