#pragma once

#include <RPC3.h>
#include "Export.h"

class MALEFICE_DLL_EXPORT RakNetUtility
{
public:
	RakNetUtility()		= delete;
	~RakNetUtility()	= delete;

	static void	logRPCRemoteError(RakNet::RPCErrorCodes errorCode, const std::string& function);
};
