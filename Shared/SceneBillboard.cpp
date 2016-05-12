#include "SceneBillboard.h"

namespace ecs
{
	SceneBillboard::SceneBillboard(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable): AScene(device, newNameTexture, newNameMesh, newPickableFlags, isCollisionable)
	{
	}

	SceneBillboard::~SceneBillboard()
	{
	}
}
