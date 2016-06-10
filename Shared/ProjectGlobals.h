#pragma once

#include <cstddef>
#include <string>
#include <irrlicht.h>
#include "Export.h"

class MALEFICE_DLL_EXPORT ProjectGlobals
{
public:
	static const std::string			GAME_NAME;
	static const bool					NO_MENU;

	static const std::size_t			NORMAL_TEAM_SIZE;
	static const std::size_t			NORMAL_TEAMS_NB;
	static const std::size_t			PREDATOR_TEAM_SIZE;
	static const std::size_t			PREDATOR_TEAMS_NB;
	static const std::size_t			MAX_PLAYERS_NB;

	static const std::string			GAME_CLIENT_VERSION;

	static const std::string			GAME_SERVER_VERSION;

	static const std::string			LOGS_DIRECTORY;
	static const std::string			GAME_CLIENT_CORE_LOG_FILEPATH;
	static const std::string			GAME_CLIENT_LAUNCHER_LOG_FILEPATH;
	static const std::string			GAME_SERVER_LOG_FILEPATH;

	static const std::string			MASTERLIST_URL;

	static const irr::core::vector3df	COLLISION_ANIMATOR_ELLIPSOID_RADIUS;
	static const irr::core::vector3df 	COLLISION_ANIMATOR_GRAVITY_PER_SECOND;
	static const irr::core::vector3df 	COLLISION_ANIMATOR_ELLIPSOID_TRANSLATION;

	static const long long				SPAWNER_VISIBILITY_TIMER;

	ProjectGlobals()	= delete;
	~ProjectGlobals()	= delete;


	/*static std::string	getGameName();

	static bool	getNoMenu();

	static std::size_t	getNormalTeamSize();
	static std::size_t	getNormalTeamsNb();
	static std::size_t	getPredatorTeamSize();
	static std::size_t	getPredatorTeamsNb();
	static std::size_t	getMaxPlayersNb();

	static std::string	getGameClientVersion();
	static std::string	getServerVersion();

	static std::string	getLogsDirectory();
	static std::string	getGameCLientCoreLogFilepath();
	static std::string	getGameClientLauncherLogFilepath();
	static std::string	getGameServerLogFilepath();

	static std::string	getMasterlistUrl();

	static irr::core::vector3df	getCollisionAnimatorEllipsoidRadius();
	static irr::core::vector3df	getCollisionAnimatorGravityPerSecond();
	static irr::core::vector3df	getCollisionAnimatorEllipsoidTranslation();*/
};
