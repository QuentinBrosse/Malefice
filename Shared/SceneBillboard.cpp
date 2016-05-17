#include "SceneBillboard.h"

namespace ecs
{
	SceneBillboard::SceneBillboard(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable): AScene(ecs::AScene::SceneType::BILLBOARD, device, newNameTexture, newNameMesh, newPickableFlags, isCollisionable)
	{
	}

	SceneBillboard::~SceneBillboard()
	{
	}


	void	SceneBillboard::dump(std::ostream& os)	const
	{
		os << "SceneBillboard {}";
	}


	void	SceneBillboard::serialize(RakNet::BitStream& out)	const
	{
		// TODO: implement serialization
	}

	void	SceneBillboard::deserialize(RakNet::BitStream& in)
	{
		// TODO: implement deserialization
	}
}
