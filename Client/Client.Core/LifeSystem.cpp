#include "LifeSystem.h"
#include "Position.h"
#include "GraphicUtil.h"
#include "Logger.h"
#include "ClientCore.h"

void	LifeSystem::die(RakNet::RakString str, RakNet::RPC3* rpc)
{
	// TODO: make "dead" disappear or something
	ecs::Position cameraPosition(
		irr::core::vector3df(50.0f, 50.0f, -60.0f),
		irr::core::vector3df(-70.0f, 30.0f, -60.0f));
	GraphicUtil::getInstance().getFPSCamera()->setPosition(cameraPosition);
	ClientCore::getInstance().getGraphicModule()->getDeadGUI()->setPseudo(str.C_String());
	ClientCore::getInstance().getGraphicModule()->getDeadGUI()->display();
}

void LifeSystem::kill(RakNet::RakString killed, RakNet::RPC3* rpc)
{
	std::string	killMsg = "You killed ";

	killMsg += killed.C_String();
	GraphicUtil::getInstance().getHUD()->displayNotification(killMsg.c_str(), 5);
	LOG_INFO(ECS) << killMsg;
}
