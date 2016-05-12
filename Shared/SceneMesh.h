#pragma once

#include "AScene.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT SceneMesh : public AScene
	{
	public:
		SceneMesh(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, bool isCollisionable, const std::string& namePK3 = "");
		virtual ~SceneMesh();

		virtual	void			setPosition(const Position& newPosition);

	private:
		irr::scene::IMeshSceneNode*	m_node;
	};
}