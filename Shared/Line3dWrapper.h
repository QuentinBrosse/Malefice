#pragma once

#include <irrlicht.h>
#include <RakNetTypes.h>
#include <BitStream.h>
#include "Export.h"

class MALEFICE_DLL_EXPORT Line3dWrapper
{
public:
	Line3dWrapper(const irr::core::line3df& line);
	Line3dWrapper();
	~Line3dWrapper() = default;

	irr::core::line3df&	getLine();

private:
	irr::core::line3df	m_line3d;
};


namespace RakNet
{
	MALEFICE_DLL_EXPORT RakNet::BitStream&	operator<<(RakNet::BitStream& out, Line3dWrapper& in);
	MALEFICE_DLL_EXPORT RakNet::BitStream&	operator>>(RakNet::BitStream& in, Line3dWrapper& out);
}