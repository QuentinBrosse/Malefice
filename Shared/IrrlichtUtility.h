#pragma once

#include <ostream>
#include <irrlicht.h>

template<typename T>
std::ostream&	operator<<(std::ostream& os, const irr::core::vector3d<T>& vector)
{
	os << "irr::core::vector3d {X = " << vector.X << ", Y = " << vector.Y << ", Z = " << vector.Z << "}";
	return os;
}
