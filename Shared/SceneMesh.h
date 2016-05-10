#pragma once

#include "Scene.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT SceneMesh : public Scene
	{
	public:
		SceneMesh(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const std::string& namePK3 = "");
		virtual ~SceneMesh();

	private:
		irr::scene::IMeshSceneNode*	m_node;
	};
}