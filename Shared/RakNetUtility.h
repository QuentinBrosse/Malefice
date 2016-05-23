#pragma once

#include <BitStream.h>
#include <RPC3.h>
#include <irrlicht.h>
#include "Export.h"

class MALEFICE_DLL_EXPORT RakNetUtility
{
public:
	RakNetUtility()		= delete;
	~RakNetUtility()	= delete;

	static void	logRPCRemoteError(RakNet::RPCErrorCodes errorCode, const std::string& function);

	template<typename T>
	static void	serializeVector(RakNet::BitStream& out, const irr::core::vector3d<T>& vector)
	{
		out.Write(vector.X);
		out.Write(vector.Y);
		out.Write(vector.Z);
	}

	template<typename T>
	static void	deserializeVector(RakNet::BitStream& in, irr::core::vector3d<T>& vector)
	{
		in.Read(vector.X);
		in.Read(vector.Y);
		in.Read(vector.Z);
	}
};
