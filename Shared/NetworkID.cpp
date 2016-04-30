#include <iostream>
#include "NetworkID.h"

namespace ecs
{
	NetworkID::NetworkID(unsigned int id) : AComponent("NetworkID", ComponentType::NETWORK_ID),
		ID(id), m_isCurrentPlayer(false)
	{

	}

	void NetworkID::dump() const
	{
		std::cout << "[NetworkID " << ID << " " << m_isCurrentPlayer << "]" << std::endl;
	}

	void NetworkID::setCurrentPlayer(bool value)
	{
		m_isCurrentPlayer = value;
	}
	bool NetworkID::isCurrentPlayer() const
	{
		return m_isCurrentPlayer;
	}
}