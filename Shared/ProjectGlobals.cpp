#include "ProjectGlobals.h"

const std::string	ProjectGlobals::GAME_NAME	= "Malefice";

const bool			ProjectGlobals::NO_MENU = false;

const std::size_t	ProjectGlobals::NORMAL_TEAM_SIZE	= 1;
const std::size_t	ProjectGlobals::NORMAL_TEAMS_NB		= 2;
const std::size_t	ProjectGlobals::PREDATOR_TEAM_SIZE	= 1;
const std::size_t	ProjectGlobals::PREDATOR_TEAMS_NB	= 1;
const std::size_t	ProjectGlobals::MAX_PLAYERS_NB		= 2;	// (ProjectGlobals::NORMAL_TEAM_SIZE * ProjectGlobals::NORMAL_TEAMS_NB) + (ProjectGlobals::PREDATOR_TEAM_SIZE * ProjectGlobals::PREDATOR_TEAMS_NB);

const std::string	ProjectGlobals::GAME_CLIENT_VERSION	= "0.1";

const std::string	ProjectGlobals::GAME_SERVER_VERSION = "0.1";

const std::string	ProjectGlobals::LOGS_DIRECTORY	= "";

const std::string	ProjectGlobals::GAME_CLIENT_CORE_LOG_FILEPATH		= ProjectGlobals::LOGS_DIRECTORY + "Client.Core.log";
const std::string	ProjectGlobals::GAME_CLIENT_LAUNCHER_LOG_FILEPATH	= ProjectGlobals::LOGS_DIRECTORY + "Client.Launcher.log";
const std::string	ProjectGlobals::GAME_SERVER_LOG_FILEPATH			= ProjectGlobals::LOGS_DIRECTORY + "Server.Core.log";

const std::string	ProjectGlobals::MASTERLIST_URL = "malefice.pinot.ovh";
