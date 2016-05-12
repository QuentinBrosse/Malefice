#pragma once

#include <iostream>
#include <string>

#include "AComponent.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT Weapon : public AComponent
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
		Weapon(const int id, const std::string& name, int maxAmmunition, int maxAmmunitionExplosive, int damage, int damageExplosive, const int maxAmmunitionLoader, const int maxAmmunitionExplosiveLoader, WeaponType weaponType, bool handToHand);
		Weapon(const Weapon& cpy);
		~Weapon()	= default;

		Weapon&				operator=(const Weapon& other);

		void				dump()							const;
		
		const int			getId()							const;
		const int			getDamage()						const;
		const int			getDamageExplosive()			const;
		const WeaponType	getWeaponType()					const;
		const bool			isHandToHand()					const;
		const std::string&	getName()						const;
		int					getAmmunition()					const;
		int					getAmmunitionExplosive()		const;
		int					getAmmunitionLoader()			const;
		int					getAmmunitionExplosiveLoader()	const;
		void				reload();
		void				reloadExplosive();

		void				fired();
		void				firedExplosive();

		void				decAmmunition(int nbFired);
		void				decAmmunitionExplosive(int nbFired);
		void				incAmmunition(int nbAmmuition);
		void				incAmmunitionExplosive(int nbAmmunition);


		virtual void	dump(std::ostream& os)	const;


	private:
		const int			ID;
		const std::string	WEAPON_NAME;
		const int			MAX_AMMUNITION;
		const int			MAX_AMMUNITION_EXPLOSIVE;
		const int			DAMAGE;
		const int			DAMAGE_EXPLOSIVE;
		const int			MAX_AMMUNITION_LOADER;
		const int			MAX_AMMUNITION_EXPLOSIVE_LOADER;
		const WeaponType	WEAPON_TYPE;
		const bool			HAND_TO_HAND;
		int					m_currentAmmunition;
		int					m_currentAmmunitionLoader;
		int					m_currentAmmunitionExplosiveLoader;
		int					m_currentAmmunitionExplosive;
	};
}
