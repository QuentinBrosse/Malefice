#pragma once

#include <iostream>
#include <string>
#include <BitStream.h>
#include "SceneAnimatedMesh.h"
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
			SHOT_GUN,
			MACHINE_GUN,
			PISTOL,
			DOUBLE_PISTOL,
			SABRE,
			CHAINSAW,
			KNIFE,
			WEAPON_COUNT
		};

		Weapon();
		Weapon(const int id, const std::string& name, const std::string& meshName, WeaponType weaponType, float distance, float precision, unsigned int ammunition, float fireRate, unsigned int ammoPerShot, unsigned int damage, unsigned int reloadTime, const Position& fpsMetrics, const Position& externalMetrics, bool sight, unsigned int defaultAmunitions);
		Weapon(const Weapon& cpy);
		~Weapon()	= default;

		void	init(const int id, const std::string& name, const std::string& meshName, WeaponType weaponType, float distance, float precision, unsigned int ammunition, float fireRate, unsigned int ammoPerShot, unsigned int damage, unsigned int reloadTime, const Position& fpsMetrics, const Position& externalMetrics, bool sight, unsigned int defaultAmunitions);

		virtual AComponent&	affect(const AComponent& rhs);
		
		const int			getId()							const;
		const int			getDamage()						const;
		const WeaponType	getWeaponType()					const;
		const std::string&	getName()						const;
		const std::string&	getMeshName()					const;
		const unsigned int	getAmmunitions()				const;
		const unsigned int	getMaxAmmunitions()				const;
		const unsigned int	getReloadTime()					const;
		const unsigned int	getAmmoPerShot()				const;
		const unsigned int	getDefaultAmunitions()			const;
		const float			getFireRate()					const;
		const float			getDistance()					const;
		Position			getFPSMetrics()					const;
		Position			getExternalMetrics()			const;
		const bool			isSight()						const;

		void				shot();
		void				reload();
		void				decAmmunition(int nbFired);
		void				incAmmunition(int nbAmmuition);

		void				createScene(irr::IrrlichtDevice* device, const bool active);

		void				setActivity(const bool active);

		SceneAnimatedMesh*	getScene()						const;

		virtual	void	dump(std::ostream& os)	const;

		virtual void	serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void	deserialize(RakNet::BitStream& in);


	private:
		static const std::string	MEDIA_PATH;

		int				m_id;
		std::string		m_weaponName;
		std::string		m_meshName;
		unsigned int	m_maxAmmunition;
		unsigned int	m_damage;
		WeaponType		m_weaponType;

		bool	m_sight;

		unsigned int	m_ammunition;
		unsigned int	m_reloadTime;
		unsigned int	m_ammoPerShot;
		unsigned int	m_defaultAmunitions;

		float	m_fireRate;
		float	m_distance;

		SceneAnimatedMesh*	m_scene;

		Position				m_externalMetrics;
		Position				m_fpsMetrics;
	};
}
