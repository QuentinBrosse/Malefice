#pragma once

#include <string>
#include "Export.h"

namespace utility
{
	class MALEFICE_DLL_EXPORT TimeUtility
	{
	public:
		TimeUtility()	= delete;
		~TimeUtility()	= delete;

		static long long	getMsTime();
		static std::string	getElapsedTimeSince(long long msTime);
	};
}
