#include "SceneBillboard.h"

namespace ecs
{
	SceneBillboard::SceneBillboard(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags): AScene(device, newNameTexture, newNameMesh, newPickableFlags)
	{

	}

	SceneBillboard::~SceneBillboard()
	{
	}


	void	SceneBillboard::dump(std::ostream& os)	const
	{
		os << "SceneBillboard {}";
	}
}
