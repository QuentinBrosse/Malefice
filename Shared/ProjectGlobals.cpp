#include "ProjectGlobals.h"


std::string	ProjectGlobals::getGameName()
{
	return "Malefice";
}


bool	ProjectGlobals::getNoMenu()
{
	return false;
}


std::size_t	ProjectGlobals::getNormalTeamSize()
{
	return 1;
}

std::size_t	ProjectGlobals::getNormalTeamsNb()
{
	return 1;
}

std::size_t	ProjectGlobals::getPredatorTeamSize()
{
	return 1;
}

std::size_t	ProjectGlobals::getPredatorTeamsNb()
{
	return 1;
}

std::size_t	ProjectGlobals::getMaxPlayersNb()
{
	return (ProjectGlobals::getNormalTeamSize() * ProjectGlobals::getNormalTeamsNb()) + (ProjectGlobals::getPredatorTeamSize() * ProjectGlobals::getPredatorTeamsNb());
}


std::string	ProjectGlobals::getGameClientVersion()
{
	return "0.1";
}

std::string	ProjectGlobals::getGameServerVersion()
{
	return "0.1";
}


std::string ProjectGlobals::getLogsDirectory()
{
	return "";
}

std::string	ProjectGlobals::getGameClientCoreLogFilepath()
{
	return ProjectGlobals::getLogsDirectory() +"Client.Core.log";
}

std::string	ProjectGlobals::getGameClientLauncherLogFilepath()
{
	return ProjectGlobals::getLogsDirectory() + "Client.Launcher.log";
}

std::string	ProjectGlobals::getGameServerLogFilepath()
{
	return ProjectGlobals::getLogsDirectory() + "Server.Core.log";
}


std::string	ProjectGlobals::getMasterlistUrl()
{
	return "malefice.pinot.ovh";
}


irr::core::vector3df	ProjectGlobals::getCollisionAnimatorEllipsoidRadius()
{
	return irr::core::vector3df(8.f, 1.f, 8.f);
}

irr::core::vector3df	ProjectGlobals::getCollisionAnimatorGravityPerSecond()
{
	return irr::core::vector3df(0.f, -9.8f, 0.f);
}

irr::core::vector3df	ProjectGlobals::getCollisionAnimatorEllipsoidTranslation()
{
	return irr::core::vector3df(0.f, 50.f, 0.f);
}


long long ProjectGlobals::getSpawnerVisibilityTimer()
{
	return 10;
}
