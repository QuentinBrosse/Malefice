#pragma once

#include "AScene.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT SceneBillboard : public AScene
	{
	public:
		SceneBillboard(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable);
		virtual ~SceneBillboard();

		virtual void	dump(std::ostream& os)	const;
	};
}
