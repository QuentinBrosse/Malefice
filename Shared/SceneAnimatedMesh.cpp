#include "SceneAnimatedMesh.h"

namespace ecs
{

	SceneAnimatedMesh::SceneAnimatedMesh(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags): Scene(device, newNameTexture, newNameMesh, newPickableFlags)
	{
	}

	SceneAnimatedMesh::~SceneAnimatedMesh()
	{
	}

}