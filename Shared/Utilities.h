#pragma once

#include <string>
#include "Export.h"

typedef unsigned long DWORD;

namespace Utilities
{
	MALEFICE_DLL_EXPORT DWORD		getSerial();
	MALEFICE_DLL_EXPORT std::string	getSerialHash();
	MALEFICE_DLL_EXPORT	long long	getMsTime();
	MALEFICE_DLL_EXPORT std::string	getElapsedTimeSince(long long msTime);

	template<class T>
	MALEFICE_DLL_EXPORT	std::string	pluralize(const std::string& word, const T& nb);
};
