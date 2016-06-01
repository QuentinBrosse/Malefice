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
			DEFAULT,
			MESH,
			ANIMATED_MESH,
			BILLBOARD,
			SCENE_COUNT
		};

		AScene();
		AScene(ecs::AScene::SceneType type);
		AScene(ecs::AScene::SceneType type, irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable);
		AScene(const AScene& cpy);
		virtual ~AScene() = 0;

		void	init(ecs::AScene::SceneType type, irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable);

		virtual irr::scene::ISceneNode*	getNode()	const	= 0;
		std::string						getNameTexture()	const;
		std::string						getNameMesh()		const;
		int								getPickableFlags()	const;
		irr::video::SMaterial*			getMaterial()		const;
		irr::scene::ITriangleSelector*	getSelector()		const;

		void					setNameTexture(const std::string& newNameTexture);
		void					setNameMesh(const std::string& newNameMesh);
		void					setPickableFlags(int newPickableFlags);
		void					setMaterial(irr::video::SMaterial* newMaterial);
		virtual	void			setPosition(const Position& newPosition) = 0;   // Will set m_node's Position and Rotation


		virtual void			dump(std::ostream& os)	const;

		virtual void			serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void			deserialize(RakNet::BitStream& in);

		virtual AComponent&		affect(const AComponent& rhs) = 0;
		virtual AComponent*	createCopy(const AComponent* rhs) const = 0;

	protected:
		ecs::AScene::SceneType			m_type;

		std::string						m_mediaPath;
		bool							m_isCollisionable;

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
