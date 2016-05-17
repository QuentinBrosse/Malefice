#include "SceneAnimatedMesh.h"
#include <iostream>

namespace ecs
{
	SceneAnimatedMesh::SceneAnimatedMesh() : AScene(ecs::AScene::SceneType::ANIMATED_MESH),
		m_node(nullptr)
	{
	}

	SceneAnimatedMesh::SceneAnimatedMesh(irr::IrrlichtDevice* device, irr::scene::ICameraSceneNode* parent, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable): AScene(ecs::AScene::SceneType::ANIMATED_MESH, device, newNameTexture, newNameMesh, newPickableFlags, isCollisionable),
		m_node(nullptr)
	{
		m_node = m_smgr->addAnimatedMeshSceneNode(m_smgr->getMesh((m_mediaPath + newNameMesh).c_str()), parent, newPickableFlags);
		m_node->setAnimationSpeed(20.f);
		if (m_isCollisionable)
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
	

	void SceneAnimatedMesh::setAnimation(irr::scene::EMD2_ANIMATION_TYPE newAnimationType)
	{
		m_node->setMD2Animation(newAnimationType);
	}

	void SceneAnimatedMesh::setTexture(const std::string& nameTexture, const bool lighting, const irr::u32 level)
	{
		m_material->setTexture(level, m_driver->getTexture((m_mediaPath + nameTexture).c_str()));
		m_material->NormalizeNormals = true;
		m_material->Lighting = lighting;
		m_node->getMaterial(0) = *m_material;
	}

	irr::scene::IAnimatedMeshSceneNode * SceneAnimatedMesh::getScene() const
	{
		return m_node;
	}


	void	SceneAnimatedMesh::dump(std::ostream& os)	const
	{
		os << "SceneAnimatedMesh {}"; // TODO: what's interesting to dump in irr::scene::IAnimatedMeshSceneNode ?
	}


	void	SceneAnimatedMesh::serialize(RakNet::BitStream& out)	const
	{
		AScene::serialize(out);
	}

	void	SceneAnimatedMesh::deserialize(RakNet::BitStream& in)
	{
		AScene::deserialize(in);
	}
}
