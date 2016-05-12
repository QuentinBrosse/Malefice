#pragma once

#include "AScene.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT SceneAnimatedMesh : public AScene
	{
	public:
		SceneAnimatedMesh(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable);
		virtual ~SceneAnimatedMesh();

		virtual void	setPosition(const ecs::Position& newPosition);
	private:
		irr::scene::IAnimatedMeshSceneNode*	m_node;

	};
}
