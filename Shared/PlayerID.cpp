#include "PlayerID.h"

namespace ecs
{
	PlayerID::PlayerID(int id) : AComponent("PlayerID", ComponentType::PLAYER_ID),
		ID(id)
	{

	}
}