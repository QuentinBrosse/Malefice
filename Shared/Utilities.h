#pragma once

#include	<windows.h>
#include	<tchar.h>

#include	<string>

#include	"Export.h"
typedef unsigned long DWORD;

namespace Utilities
{
	MALEFICE_DLL_EXPORT DWORD		GetSerial();
	MALEFICE_DLL_EXPORT std::string GetSerialHash();
};