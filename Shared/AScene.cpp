#include <map>

#include "AScene.h"

namespace ecs
{
	AScene::AScene(): AComponent("Scene", ComponentType::SCENE),
		m_type(SceneType::DEFAULT), m_mediaPath("Media/"), m_isCollisionable(false), m_selector(nullptr), m_device(nullptr), m_smgr(nullptr), m_driver(nullptr), m_nameTexture(), m_nameMesh(), m_pickableFlags(false), m_material(nullptr)
	{
	}

	AScene::AScene(ecs::AScene::SceneType type) : AComponent("Scene", ecs::AComponent::ComponentType::SCENE),
		m_type(type), m_mediaPath("Media/"), m_isCollisionable(false), m_selector(nullptr), m_device(nullptr), m_smgr(nullptr), m_driver(nullptr), m_nameTexture(), m_nameMesh(), m_pickableFlags(0), m_material(nullptr)
	{
	}

	AScene::AScene(ecs::AScene::SceneType type, irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable) : AComponent("Scene", ecs::AComponent::ComponentType::SCENE),
		m_type(type), m_mediaPath("Media/"), m_isCollisionable(isCollisionable), m_selector(nullptr), m_device(device), m_smgr(m_device->getSceneManager()), m_driver(m_device->getVideoDriver()), m_nameTexture(newNameMesh), m_nameMesh(newNameMesh), m_pickableFlags(newPickableFlags), m_material(nullptr)
	{
				
	}

	AScene::AScene(const AScene & cpy) : AComponent("Scene", ComponentType::SCENE),
		m_device(cpy.m_device), m_driver(cpy.m_driver), m_isCollisionable(cpy.m_isCollisionable), m_material(cpy.m_material), m_mediaPath(cpy.m_mediaPath), m_nameMesh(cpy.m_nameMesh), m_nameTexture(cpy.m_nameTexture), m_pickableFlags(cpy.m_pickableFlags), m_selector(cpy.m_selector), m_smgr(cpy.m_smgr), m_type(cpy.m_type)
	{
	}

	AScene::~AScene()
	{
	}

	void AScene::init(ecs::AScene::SceneType type, irr::IrrlichtDevice * device, const std::string & newNameTexture, const std::string & newNameMesh, const int newPickableFlags, const bool isCollisionable)
	{
		m_type = type;
		m_isCollisionable = isCollisionable;
		m_device = device;
		m_smgr = m_device->getSceneManager();
		m_driver = m_device->getVideoDriver();
		m_nameTexture = newNameTexture;
		m_nameMesh = newNameMesh;
		m_pickableFlags = newPickableFlags;
		m_material = nullptr;
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
		os << "AScene {MEDIA_PATH = \"" << AScene::m_mediaPath << "\", IS_COLLISIONNABLE = " << AScene::m_isCollisionable << ", nameTexture = \"" << m_nameTexture << "\", nameMash = \"" << m_nameMesh << "\", pickableFlags = " << m_pickableFlags << "}";
	}


	void	AScene::serialize(RakNet::BitStream& out, bool serializeType)	const
	{
		AComponent::serialize(out, serializeType);
		out.Write(m_type);
		out.Write(m_nameTexture);
		out.Write(m_nameMesh);
	}

	void	AScene::deserialize(RakNet::BitStream& in)
	{
		AComponent::deserialize(in);
		in.Read(m_nameTexture);
		in.Read(m_nameMesh);
	}
}
