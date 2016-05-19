#include "SceneBillboard.h"

namespace ecs
{
	SceneBillboard::SceneBillboard() : AScene(ecs::AScene::SceneType::BILLBOARD)
	{
	}

	SceneBillboard::SceneBillboard(const SceneBillboard & cpy) : AScene(cpy)
	{
	}

	SceneBillboard::SceneBillboard(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable): AScene(ecs::AScene::SceneType::BILLBOARD, device, newNameTexture, newNameMesh, newPickableFlags, isCollisionable)
	{
		init(device, newNameTexture, newNameMesh, newPickableFlags, isCollisionable);
	}

	SceneBillboard::~SceneBillboard()
	{
	}


	void	SceneBillboard::init(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable)
	{

		// TODO: implement constructor logic here
	}


	void	SceneBillboard::setPosition(const ecs::Position& newPosition)
	{
		// TODO: implement
	}


	void	SceneBillboard::dump(std::ostream& os)	const
	{
		os << "SceneBillboard {}";
	}

	AComponent & SceneBillboard::affect(const AComponent & rhs)
	{
		const SceneBillboard&	scene = dynamic_cast<const SceneBillboard&>(rhs);

		m_nameMesh = scene.m_nameMesh;
		m_nameTexture = scene.m_nameTexture;
		m_type = scene.m_type;
		return *this;
	}


	AComponent * SceneBillboard::createCopy(const AComponent * rhs) const
	{
		const SceneBillboard* scene = dynamic_cast<const SceneBillboard*>(rhs);

		return new SceneBillboard(*scene);
	}

	void	SceneBillboard::serialize(RakNet::BitStream& out, bool serializeType)	const
	{
		AScene::serialize(out, serializeType);
	}

	void	SceneBillboard::deserialize(RakNet::BitStream& in)
	{
		AScene::deserialize(in);
	}
}
