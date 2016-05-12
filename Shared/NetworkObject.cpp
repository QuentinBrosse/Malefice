#include <atomic>
#include <RakNetTypes.h>
#include "NetworkObject.h"
#include "NetworkManager.h"

NetworkObject::NetworkObject() : RakNet::NetworkIDObject()
{
	static std::atomic<RakNet::NetworkID>	networkId;

	this->SetNetworkIDManager(&NetworkManager::getInstance().getNetworkIdManager());
	this->SetNetworkID(networkId++);
}

NetworkObject::~NetworkObject()
{
}
