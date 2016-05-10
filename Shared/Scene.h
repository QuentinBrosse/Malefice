#pragma once

#include "AComponent.h"
#include <irrlicht.h>

namespace ecs
{
	class MALEFICE_DLL_EXPORT Scene : public AComponent
	{
	public:
		Scene(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags);
		virtual ~Scene() = 0;

	public:
		std::string				getNameTexture()	const;
		std::string				getNameMesh()		const;
		int						getPickableFlags()	const;
		irr::video::SMaterial*	getMaterial()		const;

		void					setNameTexture(const std::string& newNameTexture);
		void					setNameMesh(const std::string& newNameMesh);
		void					setPickableFlags(int newPickableFlags);
		void					setMaterial(irr::video::SMaterial* newMaterial);
		


	protected:
		const std::string			MEDIA_PATH;
		std::string					m_nameTexture;
		std::string					m_nameMesh;
		int							m_pickableFlags;
		irr::video::SMaterial*		m_material;
		irr::scene::ISceneManager*	m_smgr;
		irr::video::IVideoDriver*	m_driver;
		irr::IrrlichtDevice*		m_device;
	};
}