#pragma once

#include <NetworkIDManager.h>
#include "Singleton.h"
#include "Export.h"

class MALEFICE_DLL_EXPORT NetworkManager : public Singleton<NetworkManager>
{
	friend Singleton<NetworkManager>;

public:
	RakNet::NetworkIDManager&	getNetworkIdManager();


protected:
	NetworkManager()	= default;
	~NetworkManager()	= default;


private:
	RakNet::NetworkIDManager	m_networkIdManager;
};
