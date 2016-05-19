#include "SceneAnimatedMesh.h"
#include <iostream>

namespace ecs
{
	SceneAnimatedMesh::SceneAnimatedMesh() : AScene(ecs::AScene::SceneType::ANIMATED_MESH),
		m_node(nullptr)
	{
	}

	SceneAnimatedMesh::SceneAnimatedMesh(irr::IrrlichtDevice* device, irr::scene::ICameraSceneNode* parent, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable, const bool lighting, const irr::u32 level): AScene(ecs::AScene::SceneType::ANIMATED_MESH, device, newNameTexture, newNameMesh, newPickableFlags, isCollisionable),
		m_node(nullptr), m_level(level), m_lighting(lighting)
	{
		this->init(device, parent, newNameTexture, newNameMesh, newPickableFlags, isCollisionable, level, lighting);
	}

	SceneAnimatedMesh::SceneAnimatedMesh(const SceneAnimatedMesh& cpy): AScene(cpy),
		m_node(cpy.m_node), m_level(cpy.m_level), m_lighting(cpy.m_lighting)
	{

	}

	SceneAnimatedMesh::~SceneAnimatedMesh()
	{
	}

	AComponent & SceneAnimatedMesh::affect(const AComponent & rhs)
	{
		const SceneAnimatedMesh& scene = dynamic_cast<const SceneAnimatedMesh&>(rhs);

		if (scene.m_nameTexture != m_nameTexture)
			setTexture(scene.m_nameTexture);
		m_nameMesh = scene.m_nameMesh;
		m_nameTexture = scene.m_nameTexture;
		m_type = scene.m_type;

		return *this;
	}


	void	SceneAnimatedMesh::init(irr::IrrlichtDevice* device, irr::scene::ICameraSceneNode* parent, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable, const bool lighting, const irr::u32 level)
	{
		m_type = SceneType::ANIMATED_MESH;
		m_isCollisionable = isCollisionable;
		m_device = device;
		m_smgr = m_device->getSceneManager();
		m_driver = m_device->getVideoDriver();
		m_nameTexture = newNameTexture;
		m_nameMesh = newNameMesh;
		m_pickableFlags = newPickableFlags;
		m_level = level;
		m_lighting = lighting;
		m_material = nullptr;
		m_node = m_smgr->addAnimatedMeshSceneNode(m_smgr->getMesh((m_mediaPath + newNameMesh).c_str()), parent, newPickableFlags);

		if (!m_node)
		{
			std::cerr << "Mesh cannot be loaded !" << std::endl;
		}
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


	void SceneAnimatedMesh::setPosition(const ecs::Position& newPosition)
	{
		m_node->setPosition(newPosition.getVectorPosition());
		m_node->setRotation(newPosition.getVectorRotation());
		m_node->setScale(newPosition.getVectorScale());
	}
	

	void SceneAnimatedMesh::setAnimation(irr::scene::EMD2_ANIMATION_TYPE newAnimationType)
	{
		m_node->setMD2Animation(newAnimationType);
	}

	void SceneAnimatedMesh::setTexture(const std::string& nameTexture)
	{
		m_material->setTexture(m_level, m_driver->getTexture((m_mediaPath + nameTexture).c_str()));
		m_material->NormalizeNormals = true;
		m_material->Lighting = m_lighting;
		m_node->getMaterial(0) = *m_material;
		m_nameTexture = nameTexture;
	}

	irr::scene::IAnimatedMeshSceneNode * SceneAnimatedMesh::getScene() const
	{
		return m_node;
	}


	void	SceneAnimatedMesh::dump(std::ostream& os)	const
	{
		os << "SceneAnimatedMesh {}"; // TODO: what's interesting to dump in irr::scene::IAnimatedMeshSceneNode ?
	}


	void	SceneAnimatedMesh::serialize(RakNet::BitStream& out, bool serializeType)	const
	{
		AScene::serialize(out, serializeType);
	}

	void	SceneAnimatedMesh::deserialize(RakNet::BitStream& in)
	{
		AScene::deserialize(in);
	}

	AComponent * SceneAnimatedMesh::createCopy(const AComponent * rhs) const
	{
		const SceneAnimatedMesh* scene = dynamic_cast<const SceneAnimatedMesh*>(rhs);

		return new SceneAnimatedMesh(*scene);
	}
}
