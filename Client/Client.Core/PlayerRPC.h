#pragma once

#include <RPC4Plugin.h>

class PlayerRPC
{
public:
	static void	registerRPC(RakNet::RPC4* rpc);
	static void	unregisterRPC(RakNet::RPC4* rpc);


private:
	static bool	m_isRegistered;
};
