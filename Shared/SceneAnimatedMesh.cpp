#include "SceneAnimatedMesh.h"

namespace ecs
{

	SceneAnimatedMesh::SceneAnimatedMesh(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable): AScene(device, newNameTexture, newNameMesh, newPickableFlags, isCollisionable),
		m_node(nullptr)
	{
	
	}

	SceneAnimatedMesh::~SceneAnimatedMesh()
	{
	}

	void SceneAnimatedMesh::setPosition(const ecs::Position & newPosition)
	{
		m_node->setPosition(newPosition.getVectorPosition());
		m_node->setRotation(newPosition.getVectorRotation());
	}


	void	SceneAnimatedMesh::dump(std::ostream& os)	const
	{
		os << "SceneAnimatedMesh {}";
	}
}
