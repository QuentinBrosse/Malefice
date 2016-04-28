#pragma once

#include "AComponent.h"

namespace ecs
{
	class AWeapon: public AComponent
	{
	public:
		AWeapon(const std::string &name, int maxAmmunition, const int maxAmmunitionExplosive, const int damage, const int damageExplosive);
		~AWeapon();
		virtual void	dump() const;
		int			getDamage() const;
		int			getDamageExplosive() const;
		int			getAmmunition() const;
		int			getAmmunitionExplosive() const;
	private:
		const std::string	NAME;
		const int			MAX_AMMUNITION;
		const int			MAX_AMMUNITION_EXPLOSIVE;
		const int			DAMAGE;
		const int			DAMAGE_EXPLOSIVE;
		int					m_iCurrentAmmunition;
		int					m_iCurrentAmmunitionExplosive;
	};


}