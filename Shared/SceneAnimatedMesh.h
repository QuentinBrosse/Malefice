#pragma once

#include <BitStream.h>
#include "AScene.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT SceneAnimatedMesh : public AScene
	{
	public:
		SceneAnimatedMesh(irr::IrrlichtDevice* device, irr::scene::ICameraSceneNode* parent, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable);
		virtual ~SceneAnimatedMesh();

		virtual void						dump(std::ostream& os)	const;

		virtual void						setPosition(const ecs::Position& newPosition);
		void								setAnimation(irr::scene::EMD2_ANIMATION_TYPE newAnimationType);
		void								setTexture(const std::string& nameTexture, const bool lighting = true, const irr::u32 level = 0);
		irr::scene::IAnimatedMeshSceneNode*	getScene()				const;

		virtual void	serialize(RakNet::BitStream& out)	const;
		virtual void	deserialize(RakNet::BitStream& in);


	private:
		irr::scene::IAnimatedMeshSceneNode*	m_node;

	};
}
