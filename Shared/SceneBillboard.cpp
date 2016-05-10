#include "SceneBillboard.h"

namespace ecs
{
	SceneBillboard::SceneBillboard(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags): Scene(device, newNameTexture, newNameMesh, newPickableFlags)
	{

	}

	SceneBillboard::~SceneBillboard()
	{
	}
}
