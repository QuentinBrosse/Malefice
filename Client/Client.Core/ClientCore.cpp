#include "ClientCore.h"
#include "ProjectGlobals.h"
#include "GraphicUtil.h"
#include "Logger.h"
#include "NodePickable.h"
#include "mapFactory.h"
#include "PlayerFactory.h"

#include <iostream>
#include <irrlicht.h>
#include <CEGUI\CEGUI.h>
#include <CEGUI\RendererModules\Irrlicht\Renderer.h>
#include <chrono>

ClientCore::ClientCore() :
	m_networkModule(nullptr), m_isActive(true)
{
}

ClientCore::~ClientCore()
{
	if (m_networkModule->isConnected())
		m_networkModule->disconnect();
}

void	ClientCore::run()
{
	LOG_INFO(GENERAL) << "Client started.";
	if (this->init() == false)
	{
		LOG_CRITICAL(GENERAL) << "Client initialization failed. Abortring.";
		return;
	}
	LOG_INFO(GENERAL) << "Client initialized.";
	if (!ProjectGlobals::NO_MENU)
	{
		m_graphicModule->setGuiCamera();
		m_graphicModule->getMainMenu()->display();
	}
	else
	{
		m_graphicModule->setFPSCamera(0.6f);
	}
	while (this->isActive() && m_graphicModule->getDevice()->run())
	{
		this->pulse();
	}
	m_graphicModule->getDevice()->drop();
	LOG_INFO(GENERAL) << "Client stopped.";
}

bool	ClientCore::init()
{
	m_networkModule = new NetworkModule();
	if (m_networkModule->init() == false)
	{
		LOG_CRITICAL(NETWORK) << "Failed to start Network Module.";
		return false;
	}
	m_graphicModule = &(Singleton<GraphicUtil>::getInstance());
	if (m_graphicModule != nullptr)
		m_graphicModule->initGraphics();
	m_playerManager = new PlayerManager();
	createEntities();
}

void	ClientCore::pulse()
{
	if (m_networkModule != nullptr && m_networkModule->isConnected())
		m_networkModule->pulse();

	if (m_graphicModule->getDevice()->isWindowActive()) //draw only if the window is active
	{
		m_graphicModule->getMenuPause()->checkPause();

		auto begin = std::chrono::high_resolution_clock::now();
		float elapsed = fpTime(begin - m_lastTime).count();
		CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(elapsed);
		m_lastTime = begin;

		m_graphicModule->getDriver()->beginScene(true, true, irr::video::SColor(255, 150, 150, 150));
		m_graphicModule->getSceneManager()->drawAll(); //draw scene
		CEGUI::System::getSingleton().renderAllGUIContexts(); // draw gui
		m_graphicModule->CEGUIEventInjector();
		m_graphicModule->getDriver()->endScene();
	}
}


// DEBUG !
void ClientCore::createEntities()
{
	m_map = MapFactory::createMap(m_graphicModule->getDevice(), irr::core::vector3df(0.0, 0.0, 0.0), irr::core::vector3df(0.0, 0.0, 0.0), 1, "20kdm2.bsp", "map-20kdm2.pk3");
	m_predator = PlayerFactory::createPredator(irr::core::vector3df(0.0, 0.0, 0.0), irr::core::vector3df(0.0, 0.0, 0.0), 1);
}

bool	ClientCore::isActive()	const
{
	return m_isActive;
}

NetworkModule	*ClientCore::getNetworkModule()	const
{
	return m_networkModule;
}

GraphicUtil		*ClientCore::getGraphicModule() const
{
	return m_graphicModule;
}

PlayerManager*	ClientCore::getPlayerManager() const
{
	return m_playerManager;
}


void	ClientCore::setIsActive(bool isActive)
{
	m_isActive = isActive;
}
