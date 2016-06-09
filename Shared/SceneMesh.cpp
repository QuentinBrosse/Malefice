#include "SceneMesh.h"
#include "Logger.h"
#include "ProjectGlobals.h"

#include <iostream>

namespace ecs
{
	SceneMesh::SceneMesh() : AScene(ecs::AScene::SceneType::MESH),
		m_node(nullptr)
	{
	}

	SceneMesh::SceneMesh(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable, const std::string& namePK3): AScene(ecs::AScene::SceneType::MESH, device, newNameTexture, newNameMesh, newPickableFlags, isCollisionable),
		m_node(nullptr)
	{
		init(device, newNameTexture, newNameMesh, newPickableFlags, isCollisionable, namePK3);
	}

	SceneMesh::SceneMesh(const SceneMesh & cpy) : AScene(cpy),
		m_node(cpy.m_node)
	{
	}

	SceneMesh::~SceneMesh()
	{
	}


	void	SceneMesh::init(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, bool isCollisionable, const std::string& namePK3)
	{
		m_type = SceneType::MESH;
		m_isCollisionable = isCollisionable;
		m_device = device;
		m_smgr = m_device->getSceneManager();
		m_driver = m_device->getVideoDriver();
		m_nameTexture = newNameTexture;
		m_nameMesh = newNameMesh;
		m_pickableFlags = newPickableFlags;
		m_material = nullptr;
		irr::scene::IAnimatedMesh*		mesh;

		if (namePK3 != "")
		{
			m_device->getFileSystem()->addFileArchive((m_mediaPath + namePK3).c_str());
			mesh = m_smgr->getMesh(newNameMesh.c_str());
		}
		else
		{
			//TODO: constructor without decompression
		}
		if (mesh)
			m_node = m_smgr->addOctreeSceneNode(mesh->getMesh(0), 0, newPickableFlags);
		else
			LOG_ERROR(ECS) << "Error constructor SceneMesh : mesh NULL !!";

		if (m_node)
			m_node->setTriangleSelector(m_smgr->createOctreeTriangleSelector(m_node->getMesh(), m_node, 128));
		else
			LOG_ERROR(ECS) << "Error constructor SceneMesh : mesh NULL !!";

		if (m_isCollisionable)
		{
			m_selector = m_smgr->createOctreeTriangleSelector(m_node->getMesh(), m_node, 128);
			m_node->setTriangleSelector(m_selector);
			irr::scene::ISceneNodeAnimator*	animator = m_smgr->createCollisionResponseAnimator(m_selector,
				m_smgr->getActiveCamera(),
				irr::core::vector3df(30.f, 50.f, 30.f),
				ProjectGlobals::COLLISION_ANIMATOR_GRAVITY_PER_SECOND,
				irr::core::vector3df(0.f, 0.f, 0.f));
			if (m_device->getVideoDriver()->getDriverType() != irr::video::EDT_NULL)
				m_smgr->getActiveCamera()->addAnimator(animator);
			animator->drop();
		}
	}


	irr::scene::ISceneNode*	SceneMesh::getNode()	const
	{
		return m_node;
	}

	void SceneMesh::setPosition(const Position& newPosition)
	{
		m_node->setPosition(newPosition.getVectorPosition());
		m_node->setRotation(newPosition.getVectorRotation());
		m_node->setScale(newPosition.getVectorScale());
	}

	AComponent & SceneMesh::affect(const AComponent & rhs)
	{
		const SceneMesh&	scene = dynamic_cast<const SceneMesh&>(rhs);

		m_nameMesh = scene.m_nameMesh;
		m_nameTexture = scene.m_nameTexture;
		m_type = scene.m_type;
		return *this;
	}

	void SceneMesh::setCollision(bool gratity)
	{
		irr::core::vector3df g;

		m_selector = m_smgr->createOctreeTriangleSelector(m_node->getMesh(), m_node, 128);
		m_node->setTriangleSelector(m_selector);
		if (gratity)
			g = ProjectGlobals::COLLISION_ANIMATOR_GRAVITY_PER_SECOND;
		irr::scene::ISceneNodeAnimator*	animator = m_smgr->createCollisionResponseAnimator(m_selector,
			m_smgr->getActiveCamera(),
			ProjectGlobals::COLLISION_ANIMATOR_ELLIPSOID_RADIUS,
			g,
			ProjectGlobals::COLLISION_ANIMATOR_ELLIPSOID_TRANSLATION);
		m_smgr->getActiveCamera()->addAnimator(animator);
		animator->drop();
	}


	void	SceneMesh::dump(std::ostream& os)	const
	{
		os << "SceneMesh {}"; // TODO: what's interesting to dump in irr::scene::IMeshSceneNode ?
	}


	void	SceneMesh::serialize(RakNet::BitStream& out, bool serializeType)	const
	{
		AScene::serialize(out, serializeType);
	}

	void	SceneMesh::deserialize(RakNet::BitStream& in)
	{
		AScene::deserialize(in);
	}

	AComponent * SceneMesh::createCopy(const AComponent * rhs) const
	{
		const SceneMesh*	scene = dynamic_cast<const SceneMesh*>(rhs);

		return new SceneMesh(*scene);
	}
}
