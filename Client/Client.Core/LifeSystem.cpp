#include "LifeSystem.h"
#include "Position.h"
#include "GraphicUtil.h"
#include "ClientCore.h"

void	LifeSystem::die(RakNet::RPC3* rpc)
{
	// TODO: make "dead" disappear or something
	ecs::Position cameraPosition(
		irr::core::vector3df(50.0f, 50.0f, -60.0f),
		irr::core::vector3df(-70.0f, 30.0f, -60.0f));
	GraphicUtil::getInstance().getFPSCamera()->setPosition(cameraPosition);
	ClientCore::getInstance().getGraphicModule()->getDeadGUI()->display();
}
