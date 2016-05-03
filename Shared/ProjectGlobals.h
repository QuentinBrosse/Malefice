#pragma once

#include <cstddef>
#include <string>
#include "Export.h"

class MALEFICE_DLL_EXPORT ProjectGlobals
{
public:
	static const std::string	GAME_NAME;

	static const std::size_t	NORMAL_TEAM_SIZE;
	static const std::size_t	NORMAL_TEAMS_NB;
	static const std::size_t	PREDATOR_TEAM_SIZE;
	static const std::size_t	PREDATOR_TEAMS_NB;
	static const std::size_t	MAX_PLAYERS_NB;

	static const std::string	GAME_CLIENT_VERSION;

	static const std::string	GAME_SERVER_VERSION;

	static const std::string	LOGS_DIRECTORY;
	static const std::string	GAME_CLIENT_CORE_LOG_FILEPATH;
	static const std::string	GAME_CLIENT_LAUNCHER_LOG_FILEPATH;
	static const std::string	GAME_SERVER_LOG_FILEPATH;


	ProjectGlobals()	= delete;
	~ProjectGlobals()	= delete;
};
