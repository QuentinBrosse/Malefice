#include <map>

#include "AScene.h"

namespace ecs
{
	AScene::AScene(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags) : AComponent("Scene", SCENE),
		MEDIA_PATH("media/"), m_device(device), m_smgr(m_device->getSceneManager()), m_driver(m_device->getVideoDriver()), m_nameTexture(newNameMesh), m_nameMesh(newNameMesh), m_pickableFlags(newPickableFlags), m_material(nullptr)
	{
	
	}

	AScene::~AScene()
	{
	}

	std::string AScene::getNameTexture() const
	{
		return m_nameTexture;
	}

	std::string AScene::getNameMesh() const
	{
		return m_nameMesh;
	}

	int AScene::getPickableFlags() const
	{
		return m_pickableFlags;
	}

	void AScene::setNameTexture(const std::string& newNameTexture)
	{
		m_nameTexture = newNameTexture;
	}

	void AScene::setNameMesh(const std::string& newNameMesh)
	{
		m_nameMesh = newNameMesh;
	}

	void AScene::setPickableFlags(int newPickableFlags)
	{
		m_pickableFlags = newPickableFlags;
	}

	irr::video::SMaterial* AScene::getMaterial() const
	{
		return m_material;
	}

	void AScene::dump() const
	{
		std::cout << "[" << NAME << "/" << m_nameMesh << "/" << m_nameTexture << "]" << std::endl;
	}


	void AScene::setMaterial(irr::video::SMaterial* newMaterial)
	{
		m_material = newMaterial;
	}

}
