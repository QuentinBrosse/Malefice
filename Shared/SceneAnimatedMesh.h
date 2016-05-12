#pragma once

#include "AScene.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT SceneAnimatedMesh : public AScene
	{
	public:
		SceneAnimatedMesh(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags);
		virtual ~SceneAnimatedMesh();

		virtual void	dump(std::ostream& os)	const;
	};
}
