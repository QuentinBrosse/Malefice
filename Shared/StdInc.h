#pragma once

// Global includes
#include <list>
#include <map>
#include <vector>
#include <queue>

#include <string>
#include <iostream>
#include <fstream>

#include <functional>

#include <exception>


// Singleton
#include "ExplicitSingleton.h"

// OS Dependant includes
#ifdef _WIN32
#include	"../Libraries/RakNet/Source/WindowsIncludes.h"
#include	<windowsx.h>
#else
#endif

#include "Common.h"