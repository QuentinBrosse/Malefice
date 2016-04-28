
#include "PlayerRPC.h"

void	PlayerRPC::Register(RakNet::RPC4 * pRPC)
{
	if (m_bRegistered)
		return;


}

void	PlayerRPC::Unregister(RakNet::RPC4 * pRPC)
{
	if (!m_bRegistered)
		return;
}