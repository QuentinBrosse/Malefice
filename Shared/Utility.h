#pragma once

#include <string>

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/types.h>
#endif

#include "Export.h"

#ifdef _WIN32
typedef DWORD	pid_t;
#else
typedef unsigned long	DWORD;
#endif

namespace utility
{
	MALEFICE_DLL_EXPORT	DWORD		getSerial();
	MALEFICE_DLL_EXPORT	std::string	getSerialHash();
	MALEFICE_DLL_EXPORT	long long	getMsTime();
	MALEFICE_DLL_EXPORT	std::string	getElapsedTimeSince(long long msTime);

	template<class T>
	MALEFICE_DLL_EXPORT	std::string	pluralize(const std::string& word, const T& nb);

	MALEFICE_DLL_EXPORT	pid_t	getPid();
};
