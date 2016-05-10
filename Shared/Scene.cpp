#include <map>

#include "Scene.h"

namespace ecs
{
	Scene::Scene(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags) : AComponent("Scene", SCENE),
		MEDIA_PATH("../Client/Client.Core/media/"), m_device(device), m_smgr(m_device->getSceneManager()), m_driver(m_device->getVideoDriver()), m_nameTexture(newNameMesh), m_nameMesh(newNameMesh), m_pickableFlags(newPickableFlags), m_material(nullptr)
	{
	
	}

	Scene::~Scene()
	{
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

	irr::video::SMaterial* Scene::getMaterial() const
	{
		return m_material;
	}


	void Scene::setMaterial(irr::video::SMaterial* newMaterial)
	{
		m_material = newMaterial;
	}

}
