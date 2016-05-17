#include <map>

#include "AScene.h"

namespace ecs
{
	AScene::AScene(ecs::AScene::SceneType type) : AComponent("Scene", ecs::AComponent::ComponentType::SCENE),
		m_type(type), MEDIA_PATH("media/"), m_isCollisionable(false), m_selector(nullptr), m_device(nullptr), m_smgr(nullptr), m_driver(nullptr), m_nameTexture(), m_nameMesh(), m_pickableFlags(false), m_material(nullptr)
	{
	}

	AScene::AScene(ecs::AScene::SceneType type, irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable) : AComponent("Scene", ecs::AComponent::ComponentType::SCENE),
		m_type(type), MEDIA_PATH("media/"), m_isCollisionable(isCollisionable), m_selector(nullptr), m_device(device), m_smgr(m_device->getSceneManager()), m_driver(m_device->getVideoDriver()), m_nameTexture(newNameMesh), m_nameMesh(newNameMesh), m_pickableFlags(newPickableFlags), m_material(nullptr)
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
		os << "AScene {MEDIA_PATH = \"" << AScene::MEDIA_PATH << "\", IS_COLLISIONNABLE = " << AScene::m_isCollisionable << ", nameTexture = \"" << m_nameTexture << "\", nameMash = \"" << m_nameMesh << "\", pickableFlags = " << m_pickableFlags << "}";
	}


	void	AScene::serialize(RakNet::BitStream& out)	const
	{
		AComponent::serialize(out);
		// TODO: implement serialization here
	}

	void	AScene::deserialize(RakNet::BitStream& in)
	{
		AComponent::deserialize(in);
		// TODO: implement deserialization here
	}
}
