#pragma once

#include <cstddef>
#include <string>

class ProjectGlobals
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

	static const std::string	GAME_SERVER_DEFAULT_SETTINGS_FILENAME;
	static const std::string	GAME_SERVER_DEFAULT_NAME;
	static const std::string	GAME_SERVER_DEFAULT_PASSWORD;
	static const std::string	GAME_SERVER_DEFAULT_ADDRESS;
	static const short			GAME_SERVER_DEFAULT_PORT;


	ProjectGlobals()	= delete;
	~ProjectGlobals()	= delete;
};
