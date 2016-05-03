#pragma once

#include <string>
#include "AComponent.h"

namespace ecs
{
	class Weapon : public AComponent
	{
	public:
		enum WeaponType
		{
			DEFAULT,
			SNIPER_RIFLE,
			RAIL_GUN,
			SHOTGUN,
			MACHINE_GUN,
			REVOLVER,
			DOUBLE_GUN,
			SABER,
			CHAIN_SAW,
			KNIFE,
			WEAPON_COUNT
		};

		Weapon();
		Weapon(int id, const std::string& name, int maxAmmunition, int maxAmmunitionExplosive, int damage, int damageExplosive, WeaponType weaponType, bool handToHand);
		Weapon(const Weapon& cpy);
		~Weapon()	= default;

		Weapon&				operator=(const Weapon& other);

		void				dump()	const;
		
		const int			getId()						const;
		const int			getDamage()					const;
		const int			getDamageExplosive()		const;
		const WeaponType	getWeaponType()				const;
		const bool			isHandToHand()				const;
		const std::string&	getName()					const;
		int					getAmmunition()				const;
		int					getAmmunitionExplosive()	const;

		void				decAmmunition(int nbFired);
		void				decAmmunitionExplosive(int nbFired);
		void				incAmmunition(int nbAmmuition);
		void				incAmmunitionExplosive(int nbAmmunition);


	private:
		const int			ID;
		const std::string	WEAPON_NAME;
		const int			MAX_AMMUNITION;
		const int			MAX_AMMUNITION_EXPLOSIVE;
		const int			DAMAGE;
		const int			DAMAGE_EXPLOSIVE;
		const WeaponType	WEAPON_TYPE;
		const bool			HAND_TO_HAND;
		int					m_currentAmmunition;
		int					m_currentAmmunitionExplosive;
	};
}
