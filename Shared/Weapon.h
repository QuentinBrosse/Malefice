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
		};

		Weapon();
		Weapon(const std::string& name, const int maxAmmunition, const int maxAmmunitionExplosive, const int damage, const int damageExplosive, const int maxAmmunitionLoader, const int maxAmmunitionExplosiveLoader, WeaponType weaponType, bool isGun);
		Weapon(const Weapon& cpy);
		~Weapon()	= default;

		Weapon&				operator=(const Weapon& other);

		void				dump()							const;
		
		const int			getDamage()						const;
		const int			getDamageExplosive()			const;
		const WeaponType	getWeaponType()					const;
		const bool			isGun()							const;
		const std::string&	getName()						const;
		int					getAmmunition()					const;
		int					getAmmunitionExplosive()		const;
		int					getAmmunitionLoader()			const;
		int					getAmmunitionExplosiveLoader()	const;
		void				reload();
		void				reloadExplosive();

		void				fired();
		void				firedExplosive();

		void				decAmmunition(int nbLoad);
		void				decAmmunitionExplosive(int nbLoad);
		void				incAmmunition(int nbAmmuition);
		void				incAmmunitionExplosive(int nbAmmunition);


	private:
		const std::string	WEAPON_NAME;
		const int			MAX_AMMUNITION;
		const int			MAX_AMMUNITION_EXPLOSIVE;
		const int			DAMAGE;
		const int			DAMAGE_EXPLOSIVE;
		const int			MAX_AMMUNITION_LOADER;
		const int			MAX_AMMUNITION_EXPLOSIVE_LOADER;
		const WeaponType	WEAPON_TYPE;
		const bool			IS_GUN;
		int					m_currentAmmunition;
		int					m_currentAmmunitionLoader;
		int					m_currentAmmunitionExplosiveLoader;
		int					m_currentAmmunitionExplosive;
	};


}