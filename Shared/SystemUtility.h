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
	class MALEFICE_DLL_EXPORT SystemUtility
	{
	public:
		SystemUtility()		= delete;
		~SystemUtility()	= delete;

		static std::string	getSerialHash();

		static pid_t	getPid();


	private:
		static DWORD	getSerial();
	};
}
