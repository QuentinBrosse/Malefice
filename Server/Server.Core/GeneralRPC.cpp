#include "GeneralRPC.h"

bool	GeneralRPC::m_isRegistered = false;

void	GeneralRPC::registerRPC(RakNet::RPC4 * pRPC)
{
	if (m_isRegistered)
		return;
	m_isRegistered = true;
}

void	GeneralRPC::unregisterRPC(RakNet::RPC4 * pRPC)
{
	if (!m_isRegistered)
		return;
	m_isRegistered = false;
}
