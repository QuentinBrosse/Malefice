#include "RakNetUtility.h"
#include "Logger.h"

void	RakNetUtility::logRPCRemoteError(RakNet::RPCErrorCodes errorCode, const std::string& function)
{
	switch (errorCode)
	{
	case RakNet::RPC_ERROR_NETWORK_ID_MANAGER_UNAVAILABLE:
		LOG_CRITICAL(NETWORK) << "RPC3 Remote Error: {errorCode = RPC_ERROR_NETWORK_ID_MANAGER_UNAVAILABLE, function = \"" << function << "\"}.";
		break;
	case RakNet::RPC_ERROR_OBJECT_DOES_NOT_EXIST:
		LOG_CRITICAL(NETWORK) << "RPC3 Remote Error: {errorCode = RPC_ERROR_OBJECT_DOES_NOT_EXIST, function = \"" << function << "\"}.";
		break;
	case RakNet::RPC_ERROR_FUNCTION_INDEX_OUT_OF_RANGE:
		LOG_CRITICAL(NETWORK) << "RPC3 Remote Error: {errorCode = RPC_ERROR_FUNCTION_INDEX_OUT_OF_RANGE, function = \"" << function << "\"}.";
		break;
	case RakNet::RPC_ERROR_FUNCTION_NOT_REGISTERED:
		LOG_CRITICAL(NETWORK) << "RPC3 Remote Error: {errorCode = RPC_ERROR_FUNCTION_NOT_REGISTERED, function = \"" << function << "\"}.";
		break;
	case RakNet::RPC_ERROR_FUNCTION_NO_LONGER_REGISTERED:
		LOG_CRITICAL(NETWORK) << "RPC3 Remote Error: {errorCode = RPC_ERROR_FUNCTION_NO_LONGER_REGISTERED, function = \"" << function << "\"}.";
		break;
	case RakNet::RPC_ERROR_CALLING_CPP_AS_C:
		LOG_CRITICAL(NETWORK) << "RPC3 Remote Error: {errorCode = RPC_ERROR_CALLING_CPP_AS_C, function = \"" << function << "\"}.";
		break;
	case RakNet::RPC_ERROR_CALLING_C_AS_CPP:
		LOG_CRITICAL(NETWORK) << "RPC3 Remote Error: {errorCode = RPC_ERROR_CALLING_C_AS_CPP, function = \"" << function << "\"}.";
		break;
	default:
		LOG_CRITICAL(NETWORK) << "RPC3 Remote Error: {errorCode = " << static_cast<int>(errorCode) << ", function = \"" << function << "\"}.";
		break;
	}
}
