#include <chrono>
#include <irrlicht.h>
#include <CEGUI\CEGUI.h>
#include <CEGUI\RendererModules\Irrlicht\Renderer.h>
#include "ClientCore.h"
#include "ProjectGlobals.h"
#include "GraphicUtil.h"
#include "Logger.h"
#include "NodePickable.h"
#include "mapFactory.h"
#include "PlayerFactory.h"
#include "PositionSystem.h"
#include "WeaponManager.h"
#include "WeaponManagerSystem.h"
#include "EventSystem.h"
#include "GameEventReceiver.h"
#include "WeaponManagerSystem.h"

ClientCore::ClientCore() : Singleton<ClientCore>(), NetworkObject(NetworkRPC::ReservedNetworkIds::ClientCore),
	m_networkModule(nullptr), m_graphicModule(nullptr), m_playerManager(nullptr), m_clientId(), m_isActive(true), m_map(nullptr), m_player(nullptr)
{
}

ClientCore::~ClientCore()
{
	if (m_networkModule->getConnectionState() == RakNet::ConnectionState::IS_CONNECTED)
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
		m_graphicModule->setFPSCamera();
		createEntities();
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
	m_graphicModule = &GraphicUtil::getInstance();
	m_playerManager = new PlayerManager();
}

void	ClientCore::pulse()
{
	if (m_networkModule != nullptr && (m_networkModule->getConnectionState() == RakNet::ConnectionState::IS_CONNECTED || m_networkModule->getConnectionState() == RakNet::ConnectionState::IS_CONNECTING))
		m_networkModule->pulse();

	if (m_graphicModule->getDevice()->isWindowActive()) //draw only if the window is active
	{
		m_graphicModule->getDevice()->setEventReceiver(&m_graphicModule->getCEGUIEventReceiver());
		m_graphicModule->getMenuPause()->checkPause();
		m_graphicModule->getWaitingRoom()->refreshTime();
		m_graphicModule->getHUD()->refreshTime();

		auto begin = std::chrono::high_resolution_clock::now();
		float elapsed = fpTime(begin - m_lastTime).count();
		CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(elapsed);
		m_lastTime = begin;

		std::cout << "Bwaaa: " << m_graphicModule->getMenuPause()->getEnableStatus() << std::endl;
		if (!m_graphicModule->getMenuPause()->getEnableStatus() && m_player)
		{
			ecs::PositionSystem::update(*m_player);
			ecs::EventSystem::doEvents(*m_player);
		}
		
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
	m_map = MapFactory::createMap(m_graphicModule->getDevice(), irr::core::vector3df(-1350, -130, -1400), irr::core::vector3df(0.0, 0.0, 0.0), 1, "20kdm2.bsp", "map-20kdm2.pk3");
	ecs::PositionSystem::initScenePosition(*m_map);
	m_player = PlayerFactory::createPlayer(m_graphicModule->getDevice(), "sydney.bmp", "sydney.md2", 2, irr::core::vector3df(-1350, -130, -1400), irr::core::vector3df(0.0, 0.0, 0.0), 1, 100);
	ecs::PositionSystem::initScenePosition(*m_player);
	ecs::WeaponManagerSystem::initWeapon(*m_player);
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

ecs::Entity* ClientCore::getMap() const
{
	return m_map;
}


void	ClientCore::setIsActive(bool isActive)
{
	m_isActive = isActive;
}

void	ClientCore::setClientId(ecs::ClientId clientId, RakNet::RPC3* rpc)
{
	RakNet::RakString	nickname = m_nickname.c_str();

	m_clientId = clientId;
	LOG_INFO(NETWORK) << "Server accepted connection, clientId = " << m_clientId << ".";
	m_networkModule->callRPC(NetworkRPC::PLAYER_MANAGER_SET_PLAYER_NICKNAME, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::PlayerManager), nickname);
	LOG_DEBUG(NETWORK) << "Sent nickname \"" << nickname << "\" to server";
}

void	ClientCore::setNickname(const std::string& nickname)
{
	m_nickname = nickname;
}
