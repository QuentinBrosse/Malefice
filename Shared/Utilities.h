#pragma once

#ifdef _WIN32
#include	<windows.h>
#include	<mmsystem.h>
#include	<direct.h>
#include	<tlhelp32.h>
#include	<time.h>
#endif
#include	<tchar.h>

#include	<string>
#include	<stdarg.h>
#include	<memory>

#include	"Export.h"
typedef unsigned long DWORD;

namespace Utilities
{
	MALEFICE_DLL_EXPORT DWORD			GetSerial();
	MALEFICE_DLL_EXPORT std::string		GetSerialHash();
	MALEFICE_DLL_EXPORT	unsigned long	GetTime();
	MALEFICE_DLL_EXPORT	std::string		FormatString(const std::string fmt_str, ...);
	MALEFICE_DLL_EXPORT std::string		GetTimePassedFromTime(unsigned long time);
};