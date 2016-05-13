#include "SceneAnimatedMesh.h"
#include <iostream>

namespace ecs
{

	SceneAnimatedMesh::SceneAnimatedMesh(irr::IrrlichtDevice* device, irr::scene::ICameraSceneNode* parent, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable): AScene(device, newNameTexture, newNameMesh, newPickableFlags, isCollisionable),
		m_node(nullptr)
	{
		m_node = m_smgr->addAnimatedMeshSceneNode(m_smgr->getMesh((MEDIA_PATH + newNameMesh).c_str()), parent, newPickableFlags);
		m_node->setAnimationSpeed(20.f);
		if (IS_COLLISIONABLE)
		{
			m_selector = m_smgr->createOctreeTriangleSelector(m_node->getMesh(), m_node, 128);
			m_node->setTriangleSelector(m_selector);
			//m_selector->drop(); TODO if memory leak
		}
		m_material = new irr::video::SMaterial();

		if (newNameTexture != "")
			setTexture(newNameTexture);
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

	void SceneAnimatedMesh::setAnimation(irr::scene::EMD2_ANIMATION_TYPE newAnimationType)
	{
		m_node->setMD2Animation(newAnimationType);
	}

	void SceneAnimatedMesh::setTexture(const std::string& nameTexture, const bool lighting, const irr::u32 level)
	{
		m_material->setTexture(level, m_driver->getTexture((MEDIA_PATH + nameTexture).c_str()));
		m_material->NormalizeNormals = true;
		m_material->Lighting = lighting;
		m_node->getMaterial(0) = *m_material;
	}

	irr::scene::IAnimatedMeshSceneNode * SceneAnimatedMesh::getScene() const
	{
		return m_node;
	}

}
