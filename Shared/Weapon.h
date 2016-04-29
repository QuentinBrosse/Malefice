#pragma once

#include "AComponent.h"

namespace ecs
{
	class Weapon : public AComponent
	{
	public:
		typedef enum
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
		} WeaponType;

	public:
		Weapon();
		Weapon(const std::string& sName, int iMaxAmmunition, const int iMaxAmmunitionExplosive, const int iDamage, const int iDamageExplosive, const WeaponType eWeaponType, const bool bIsGun);
		Weapon(const Weapon& cCpy);
		~Weapon() = default;
		Weapon&				operator=(const Weapon&);
		void				dump() const;
		int					getDamage() const;
		int					getDamageExplosive() const;
		int					getAmmunition() const;
		int					getAmmunitionExplosive() const;
		const bool			isGun() const;
		const std::string&	getName() const;
	private:
		const std::string	WEAPON_NAME;
		const int			MAX_AMMUNITION;
		const int			MAX_AMMUNITION_EXPLOSIVE;
		const int			DAMAGE;
		const int			DAMAGE_EXPLOSIVE;
		const WeaponType	WEAPON_TYPE;
		const bool			IS_GUN;
		int					m_iCurrentAmmunition;
		int					m_iCurrentAmmunitionExplosive;
	};


}