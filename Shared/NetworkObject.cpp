#include <atomic>
#include <RakNetTypes.h>
#include "NetworkObject.h"
#include "NetworkManager.h"

NetworkObject::NetworkObject(NetworkRPC::ReservedNetworkIds networkId) : RakNet::NetworkIDObject()
{
	static std::atomic<RakNet::NetworkID>	nextNetworkId{static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::UnreservedStart)};

	this->SetNetworkIDManager(&NetworkManager::getInstance().getNetworkIdManager());
	if (networkId == NetworkRPC::ReservedNetworkIds::None)
		this->SetNetworkID(nextNetworkId++);
	else
		this->SetNetworkID(static_cast<RakNet::NetworkID>(networkId));
}

NetworkObject::~NetworkObject()
{
}
