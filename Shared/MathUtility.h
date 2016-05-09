#pragma once

#include "Export.h"

namespace utility
{

	class MALEFICE_DLL_EXPORT MathUtility
	{
	public:
		MathUtility() = delete;
		~MathUtility() = delete;
		
		static const float	PI;

		static float		degreesToRadians(float degrees);
	};
}