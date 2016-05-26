#include "Line3dWrapper.h"
#include "RakNetUtility.h"

Line3dWrapper::Line3dWrapper(const irr::core::line3df& line)
{
	m_line3d = line;
}

Line3dWrapper::Line3dWrapper():
	m_line3d()
{

}

irr::core::line3df& Line3dWrapper::getLine()
{
	return m_line3d;
}

RakNet::BitStream&	RakNet::operator<<(RakNet::BitStream& out, Line3dWrapper & in)
{
	RakNetUtility::serializeLine(out, in.getLine());

	return out;
}

RakNet::BitStream&	RakNet::operator>>(RakNet::BitStream& in, Line3dWrapper& out)
{
	RakNetUtility::deserializeLine(in, out.getLine());

	return in;
}