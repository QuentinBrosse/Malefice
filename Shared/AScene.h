#pragma once

#include "AComponent.h"
#include "Position.h"

#include <irrlicht.h>

namespace ecs
{
	class MALEFICE_DLL_EXPORT AScene : public AComponent
	{
	public:
		AScene(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable);
		virtual ~AScene() = 0;

	public:
		std::string				getNameTexture()	const;
		std::string				getNameMesh()		const;
		int						getPickableFlags()	const;
		irr::video::SMaterial*	getMaterial()		const;

		void					dump()				const;

		void					setNameTexture(const std::string& newNameTexture);
		void					setNameMesh(const std::string& newNameMesh);
		void					setPickableFlags(int newPickableFlags);
		void					setMaterial(irr::video::SMaterial* newMaterial);
		
		virtual	void			setPosition(const Position& newPosition) = 0;   // Will set m_node's Position and Rotation

	protected:
		const std::string			MEDIA_PATH;
		const bool					IS_COLLISIONABLE;

		irr::scene::ITriangleSelector*	m_selector;
		std::string						m_nameTexture;
		std::string						m_nameMesh;
		int								m_pickableFlags;
		irr::IrrlichtDevice*			m_device;
		irr::video::SMaterial*			m_material;
		irr::scene::ISceneManager*		m_smgr;
		irr::video::IVideoDriver*		m_driver;
	};
}