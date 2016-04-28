#include "NetworkID.h"

namespace ecs
{
	NetworkID::NetworkID(networkID id) : AComponent("NetworkID", ComponentType::NETWORK_ID),
		ID(id), m_bIsCurrentPlayer(false)
	{

	}

	void NetworkID::dump() const
	{
		std::cout << "[NetworkID " << ID << " " << m_bIsCurrentPlayer << "]" << std::endl;
	}

	void NetworkID::setCurrentPlayer(bool value)
	{
		m_bIsCurrentPlayer = value;
	}
	bool NetworkID::isCurrentPlayer() const
	{
		return m_bIsCurrentPlayer;
	}
}