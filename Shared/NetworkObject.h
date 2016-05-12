#pragma once

#include <NetworkIDObject.h>
#include "Export.h"

class MALEFICE_DLL_EXPORT NetworkObject : public RakNet::NetworkIDObject
{
public:
	NetworkObject();
	virtual ~NetworkObject()	= 0;
};
