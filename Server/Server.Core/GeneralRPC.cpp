
#include "GeneralRPC.h"

bool	GeneralRPC::m_bRegistered = false;

void	GeneralRPC::Register(RakNet::RPC4 * pRPC)
{
	if (m_bRegistered)
		return;

	m_bRegistered = true;
}

void	GeneralRPC::Unregister(RakNet::RPC4 * pRPC)
{
	if (!m_bRegistered)
		return;

	m_bRegistered = false;
}