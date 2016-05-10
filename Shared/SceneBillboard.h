#pragma once

#include "Scene.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT SceneBillboard : public Scene
	{
	public:
		SceneBillboard(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags);
		virtual ~SceneBillboard();
	private:
	};

}