#pragma once

#include <NetworkIDObject.h>
#include "NetworkRPC.h"
#include "Export.h"

class MALEFICE_DLL_EXPORT NetworkObject : public RakNet::NetworkIDObject
{
public:
	NetworkObject(NetworkRPC::ReservedNetworkIds networkId = NetworkRPC::ReservedNetworkIds::None);
	virtual ~NetworkObject()	= 0;
};
