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
			WEAPON_COUNT
		};

		Weapon();
		Weapon(const int id, const std::string& name, WeaponType weaponType, float distance, float precision, unsigned int ammunition, float fireRate, unsigned int ammoPerShot, unsigned int damage, unsigned int reloadTime, irr::core::vector3df	fpsMetricsPosition, irr::core::vector3df fpsMetricsRotation, irr::core::vector3df fpsMetricsScale, irr::core::vector3df	externalMetricsPosition, irr::core::vector3df externalMetricsRotation, irr::core::vector3df	externalMetricsScale, bool sight);
		Weapon(const Weapon& cpy);
		~Weapon()	= default;

		Weapon&				operator=(const Weapon& other);
		
		const int			getId()							const;
		const int			getDamage()						const;
		const WeaponType	getWeaponType()					const;
		const std::string&	getName()						const;
		const unsigned int	getAmmunitions()				const;
		const unsigned int	getMaxAmmunitions()				const;
		const unsigned int	getReloadTime()					const;
		const unsigned int	getAmmoPerShot()				const;
		const float			getFireRate()					const;
		const float			getDistance()					const;
		irr::core::vector3df getFPSMetricsPosition()		const;
		irr::core::vector3df getFPSMetricsRotation()		const;
		irr::core::vector3df getFPSMetricsScale()			const;
		irr::core::vector3df getExternalMetricsPosition()	const;
		irr::core::vector3df getExternalMetricsRotation()	const;
		irr::core::vector3df getExternalMetricsScale()		const;
		const bool			isSight() const;
		void				shot();
		void				reload();
		void				decAmmunition(int nbFired);
		void				incAmmunition(int nbAmmuition);

		void				createScene(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const bool active);

		void setActivity(const bool active);

		SceneAnimatedMesh*	getScene()						const;

		virtual	void	dump(std::ostream& os)	const;

		virtual void	serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void	deserialize(RakNet::BitStream& in);


	private:
		int				m_id;
		std::string		m_weaponName;
		unsigned int	m_maxAmmunition;
		unsigned int	m_damage;
		WeaponType		m_weaponType;

		bool	m_sight;

		unsigned int	m_ammunition;
		unsigned int	m_reloadTime;
		unsigned int	m_ammoPerShot;

		float	m_fireRate;
		float	m_distance;

		SceneAnimatedMesh*	m_scene;

		irr::core::vector3df	m_fpsMetricsPosition;
		irr::core::vector3df	m_fpsMetricsRotation;
		irr::core::vector3df	m_fpsMetricsScale;
		irr::core::vector3df	m_externalMetricsPosition;
		irr::core::vector3df	m_externalMetricsRotation;
		irr::core::vector3df	m_externalMetricsScale;
	};
}
