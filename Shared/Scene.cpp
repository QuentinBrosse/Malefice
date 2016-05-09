#include "Scene.h"

namespace ecs
{
	Scene::Scene(irr::scene::ISceneManager * newSmgr, irr::video::IVideoDriver * newDriver, const std::string & newNameTexture, std::string & newNameMesh, int newPickableFlags) :
		AComponent("Scene", SCENE), m_smgr(newSmgr), m_driver(newDriver), m_nameTexture(newNameMesh), m_nameMesh(newNameMesh), m_pickableFlags(newPickableFlags), m_node(nullptr), m_material(nullptr)
	{
	}

	Scene::~Scene()
	{
	}

	irr::scene::ISceneManager* Scene::getSmgr() const
	{
		return m_smgr;
	}

	irr::video::IVideoDriver* Scene::getDriver() const
	{
		return m_driver;
	}

	std::string Scene::getNameTexture() const
	{
		return m_nameTexture;
	}

	std::string Scene::getNameMesh() const
	{
		return m_nameMesh;
	}

	int Scene::getPickableFlags() const
	{
		return m_pickableFlags;
	}

	void Scene::setSmgr(irr::scene::ISceneManager* newSmgr)
	{
		m_smgr = newSmgr;
	}

	void Scene::setDriver(irr::video::IVideoDriver* newDriver)
	{
		m_driver = newDriver;
	}

	void Scene::setNameTexture(const std::string& newNameTexture)
	{
		m_nameTexture = newNameTexture;
	}

	void Scene::setNameMesh(const std::string& newNameMesh)
	{
		m_nameMesh = newNameMesh;
	}

	void Scene::setPickableFlags(int newPickableFlags)
	{
		m_pickableFlags = newPickableFlags;
	}

	irr::scene::IAnimatedMeshSceneNode* Scene::getNode() const
	{
		return m_node;
	}

	irr::video::SMaterial* Scene::getMaterial() const
	{
		return m_material;
	}
}
void Scene::setNode(irr::scene::IAnimatedMeshSceneNode* newNode)
{
	m_node = newNode;
}


void Scene::setMaterial(irr::video::SMaterial* newMaterial)
{
	m_material = newMaterial;
}
