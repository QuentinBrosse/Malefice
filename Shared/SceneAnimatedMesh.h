#pragma once

#include "Scene.h"

namespace ecs
{

	class MALEFICE_DLL_EXPORT SceneAnimatedMesh : public Scene
	{
	public:
		SceneAnimatedMesh(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags);
		virtual ~SceneAnimatedMesh();

	private:

	};

}