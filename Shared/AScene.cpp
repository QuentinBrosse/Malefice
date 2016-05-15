#include <map>

#include "AScene.h"

namespace ecs
{
	AScene::AScene(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable) : AComponent("Scene", SCENE),
		MEDIA_PATH("media/"), m_device(device), m_smgr(m_device->getSceneManager()), m_driver(m_device->getVideoDriver()), m_nameTexture(newNameMesh), m_nameMesh(newNameMesh), m_pickableFlags(newPickableFlags), m_material(nullptr), IS_COLLISIONABLE(isCollisionable), m_selector(nullptr)
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

	irr::video::SMaterial* AScene::getMaterial() const
	{
		return m_material;
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

	void AScene::setMaterial(irr::video::SMaterial* newMaterial)
	{
		m_material = newMaterial;
	}


	void	AScene::dump(std::ostream& os)	const
	{
		os << "AScene {NAME = " << NAME << ", nameMash = \"" << m_nameMesh << "\", nameTexture = \"" << m_nameTexture << "\"}";
	}


	void	AScene::serialize(RakNet::BitStream& out)	const
	{
		// TODO: implement serialization
	}

	void	AScene::deserialize(RakNet::BitStream& in)
	{
		// TODO: implement deserialization
	}
}
