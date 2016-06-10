#pragma once

#include <cstddef>
#include <string>
#include <irrlicht.h>
#include "Export.h"

class MALEFICE_DLL_EXPORT ProjectGlobals
{
public:
	ProjectGlobals()	= delete;
	~ProjectGlobals()	= delete;


	static std::string	getGameName();

	static bool	getNoMenu();

	static std::size_t	getNormalTeamSize();
	static std::size_t	getNormalTeamsNb();
	static std::size_t	getPredatorTeamSize();
	static std::size_t	getPredatorTeamsNb();
	static std::size_t	getMaxPlayersNb();


	static std::string	getGameClientVersion();
	static std::string	getGameServerVersion();

	static std::string	getLogsDirectory();
	static std::string	getGameClientCoreLogFilepath();
	static std::string	getGameClientLauncherLogFilepath();
	static std::string	getGameServerLogFilepath();

	static std::string	getMasterlistUrl();
	static std::string	getMasterlistUrlServer();

	static irr::core::vector3df	getCollisionAnimatorEllipsoidRadius();
	static irr::core::vector3df	getCollisionAnimatorGravityPerSecond();
	static irr::core::vector3df	getCollisionAnimatorEllipsoidTranslation();

	static long long getSpawnerVisibilityTimer();
};
