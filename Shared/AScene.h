#pragma once

#include <irrlicht.h>
#include <BitStream.h>
#include "AComponent.h"
#include "Position.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT AScene : public AComponent
	{
	public:
		enum class SceneType : int
		{
			MESH,
			ANIMATED_MESH,
			BILLBOARD,
			SCENE_COUNT
		};

		AScene(ecs::AScene::SceneType type, irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable);
		virtual ~AScene() = 0;

		std::string				getNameTexture()	const;
		std::string				getNameMesh()		const;
		int						getPickableFlags()	const;
		irr::video::SMaterial*	getMaterial()		const;

		void					setNameTexture(const std::string& newNameTexture);
		void					setNameMesh(const std::string& newNameMesh);
		void					setPickableFlags(int newPickableFlags);
		void					setMaterial(irr::video::SMaterial* newMaterial);
		virtual	void			setPosition(const Position& newPosition) = 0;   // Will set m_node's Position and Rotation


		virtual void	dump(std::ostream& os)	const;

		virtual void	serialize(RakNet::BitStream& out)	const;
		virtual void	deserialize(RakNet::BitStream& in);


	protected:
		ecs::AScene::SceneType	m_type;

		const std::string	MEDIA_PATH;
		const bool			IS_COLLISIONABLE;

		irr::scene::ITriangleSelector*	m_selector;
		irr::IrrlichtDevice*			m_device;
		irr::scene::ISceneManager*		m_smgr;
		irr::video::IVideoDriver*		m_driver;
		std::string						m_nameTexture;
		std::string						m_nameMesh;
		int								m_pickableFlags;
		irr::video::SMaterial*			m_material;
	};
}
