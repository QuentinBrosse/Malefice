#pragma once

#ifdef MALEFICE_SHARED_DLL
#define MALEFICE_DLL_EXPORT __declspec(dllexport)
#else
#define MALEFICE_DLL_EXPORT __declspec(dllimport)
#endif
