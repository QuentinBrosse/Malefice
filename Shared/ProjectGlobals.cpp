#include "ProjectGlobals.h"

const std::string	ProjectGlobals::GAME_NAME	= "Malefice";

const bool			ProjectGlobals::NO_MENU = false;

const std::size_t	ProjectGlobals::NORMAL_TEAM_SIZE	= 1;
const std::size_t	ProjectGlobals::NORMAL_TEAMS_NB		= 2;
const std::size_t	ProjectGlobals::PREDATOR_TEAM_SIZE	= 1;
const std::size_t	ProjectGlobals::PREDATOR_TEAMS_NB	= 0;
const std::size_t	ProjectGlobals::MAX_PLAYERS_NB = (ProjectGlobals::NORMAL_TEAM_SIZE * ProjectGlobals::NORMAL_TEAMS_NB) + (ProjectGlobals::PREDATOR_TEAM_SIZE * ProjectGlobals::PREDATOR_TEAMS_NB);

const std::string	ProjectGlobals::GAME_CLIENT_VERSION	= "0.1";

const std::string	ProjectGlobals::GAME_SERVER_VERSION = "0.1";

const std::string	ProjectGlobals::LOGS_DIRECTORY	= "";

const std::string	ProjectGlobals::GAME_CLIENT_CORE_LOG_FILEPATH		= ProjectGlobals::LOGS_DIRECTORY + "Client.Core.log";
const std::string	ProjectGlobals::GAME_CLIENT_LAUNCHER_LOG_FILEPATH	= ProjectGlobals::LOGS_DIRECTORY + "Client.Launcher.log";
const std::string	ProjectGlobals::GAME_SERVER_LOG_FILEPATH			= ProjectGlobals::LOGS_DIRECTORY + "Server.Core.log";

const std::string	ProjectGlobals::MASTERLIST_URL = "malefice.pinot.ovh";

const irr::core::vector3df	ProjectGlobals::COLLISION_ANIMATOR_ELLIPSOID_RADIUS = irr::core::vector3df(8.f, 1.f, 8.f);
const irr::core::vector3df 	ProjectGlobals::COLLISION_ANIMATOR_GRAVITY_PER_SECOND = irr::core::vector3df(0.f, -9.8f, 0.f);
const irr::core::vector3df 	ProjectGlobals::COLLISION_ANIMATOR_ELLIPSOID_TRANSLATION = irr::core::vector3df(0.f, 50.f, 0.f);
