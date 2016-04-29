#pragma once

#include "AComponent.h"

namespace ecs
{
	class Weapon : public AComponent
	{
	public:
		Weapon(const std::string &name, int maxAmmunition, const int maxAmmunitionExplosive, const int damage, const int damageExplosive, bool isGun);
		Weapon(const Weapon& cpy);
		~Weapon() = default;
		void			dump() const;
		int				getDamage() const;
		int				getDamageExplosive() const;
		int				getAmmunition() const;
		int				getAmmunitionExplosive() const;
		const bool		isGun() const;
	private:
		const std::string	NAME;
		const int			MAX_AMMUNITION;
		const int			MAX_AMMUNITION_EXPLOSIVE;
		const int			DAMAGE;
		const int			DAMAGE_EXPLOSIVE;
		const bool			IS_GUN;
		int					m_iCurrentAmmunition;
		int					m_iCurrentAmmunitionExplosive;
	};


}