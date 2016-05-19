#pragma once

#include "Export.h"

namespace utility
{
	class MALEFICE_DLL_EXPORT MathUtility
	{
	public:
		static const float	PI;

		MathUtility()	= delete;
		~MathUtility()	= delete;
		
		static float	degreesToRadians(float degrees);
	};
}
