#include "SceneBillboard.h"

namespace ecs
{
	SceneBillboard::SceneBillboard() : AScene(ecs::AScene::SceneType::BILLBOARD)
	{
	}

	SceneBillboard::SceneBillboard(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable): AScene(ecs::AScene::SceneType::BILLBOARD, device, newNameTexture, newNameMesh, newPickableFlags, isCollisionable)
	{
	}

	SceneBillboard::~SceneBillboard()
	{
	}

	void	SceneBillboard::setPosition(const ecs::Position& newPosition)
	{
		// TODO: implement
	}


	void	SceneBillboard::dump(std::ostream& os)	const
	{
		os << "SceneBillboard {}";
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
