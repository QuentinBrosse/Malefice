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
		Weapon(const int id, const std::string& name, const std::string& meshName, WeaponType weaponType, float distance, float precision, unsigned int maxAmmunition, float fireRate, unsigned int ammoPerShot, unsigned int damage, unsigned int reloadTime, const Position& fpsMetrics, const irr::core::vector3df fpsMetricsOffset, float fpsMetricsCoefOffset, const Position& externalMetrics, bool sight, unsigned int maxAmunitionsClip);
		Weapon(const Weapon& cpy);
		~Weapon();

		void	init(const int id, const std::string& name, const std::string& meshName, WeaponType weaponType, float distance, float precision, unsigned int maxAmmunitions, float fireRate, unsigned int ammoPerShot, unsigned int damage, unsigned int reloadTime, const Position& fpsMetrics, const irr::core::vector3df fpsMetricsOffset, float fpsMetricsCoefOffset, const Position& externalMetrics, bool sight, unsigned int maxAmunitionsClip);

		virtual AComponent&		affect(const AComponent& rhs);
		
		const int				getId()							const;
		const int				getDamage()						const;
		const WeaponType		getWeaponType()					const;
		const std::string&		getName()						const;
		const std::string&		getMeshName()					const;
		const unsigned int		getAmmunitions()				const;
		const unsigned int		getMaxAmmunitions()				const;
		const unsigned int		getReloadTime()					const;
		const unsigned int		getAmmoPerShot()				const;
		const unsigned int		getMaxAmmunitionsClip()			const;
		const unsigned int		getAmmunitionsClip()			const;
		const float				getFireRate()					const;
		const float				getDistance()					const;
		Position				getFPSMetrics()					const;
		irr::core::vector3df	getFPSMetricsOffset()			const;
		float					getFPSMetricsCoefOffset()		const;
		Position				getExternalMetrics()			const;
		const bool				isSight()						const;

		bool					shoot();
		void					reload();
		void					decAmmunition(int nbLoaded);
		void					incAmmunition(int nbAmmunition);

		void					createScene(irr::IrrlichtDevice* device, irr::scene::ISceneNode* parent, const bool active);

		void					setActivity(const bool active);

		SceneAnimatedMesh*		getScene()						const;

		virtual	void			dump(std::ostream& os)	const;

		virtual AComponent*		createCopy(const AComponent* rhs) const;

		virtual void			serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void			deserialize(RakNet::BitStream& in);

	private:
		static const std::string	MEDIA_PATH;

		int				m_id;
		std::string		m_weaponName;
		std::string		m_meshName;
		unsigned int	m_maxAmmunitions;			// Max ammunition total
		unsigned int	m_maxAmmunitionsClip;		//	Max Ammunition in clip
		unsigned int	m_damage;
		WeaponType		m_weaponType;

		bool	m_sight;

		unsigned int	m_reloadTime;
		unsigned int	m_ammoPerShot;
		unsigned int	m_ammunitions;
		unsigned int	m_ammunitionsClip;

		float					m_fireRate;
		float					m_distance;

		SceneAnimatedMesh*		m_scene;

		Position				m_fpsMetrics;
		irr::core::vector3df	m_fpsMetricsOffset;
		float					m_fpsMetricsCoefOffset;
		Position				m_externalMetrics;

	};
}
