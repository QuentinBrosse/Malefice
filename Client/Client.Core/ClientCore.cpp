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
#include "Position.h"
#include "PositionSystem.h"
#include "WeaponManager.h"
#include "WeaponManagerSystem.h"
#include "EventSystem.h"
#include "WeaponManagerSystem.h"
#include "TimeUtility.h"
#include "Armor.h"
#include "MasterList.h"
#include "Target.h"

ClientCore::ClientCore() : Singleton<ClientCore>(), NetworkObject(NetworkRPC::ReservedNetworkIds::ClientCore),
	m_networkModule(nullptr), m_graphicModule(nullptr), m_playerManager(nullptr), m_masterList(nullptr), m_clientId(), m_isActive(true), m_map(nullptr), m_player(nullptr), m_player_ia(nullptr)
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
		startGame(0);
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
	m_playerManager = &PlayerManager::getInstance();
	m_masterList = &MasterListNetwork::getInstance();

	std::vector<std::string> datas = m_masterList->fetch();
	LOG_DEBUG(GENERAL) << "Server master list size: " + std::to_string(datas.size());
	for (auto it : datas)
	{
		std::string ip = it.substr(0, it.find(":"));
		it = it.substr(it.find(":") + 1);
		std::string port = it.substr(0, it.find(":"));
		it = it.substr(it.find(":") + 1);
		std::string players = it;

		m_graphicModule->getMasterList()->addServer(ip, port, false, std::stoi(players));
	}

	m_masterList->fetch();
	m_graphicModule->getHUD()->displayNotification("Oklm...", 30);
	m_graphicModule->getHUD()->displayNotification("Un lama ! Un lamastico !!!", 33);
	m_graphicModule->getHUD()->displayNotification("Une notification !", 40);
	m_graphicModule->getHUD()->displayNotification("Une autre !", 42);
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
		m_graphicModule->getConnectWindow()->checkConnectionStatus();
		m_graphicModule->getWaitingRoom()->checkConnectedPlayers();
		m_graphicModule->getHUD()->refreshEventDisplay();

		if (m_graphicModule->getHUD()->isActive())
		{
			ecs::WeaponManager*	weaponManager = dynamic_cast<ecs::WeaponManager*>((*m_playerManager->getCurrentPlayer())[ecs::AComponent::ComponentType::WEAPON_MANAGER]);
			ecs::Life* life = dynamic_cast<ecs::Life*>((*m_playerManager->getCurrentPlayer())[ecs::AComponent::ComponentType::LIFE]);
			ecs::Armor* armor = dynamic_cast<ecs::Armor*>((*m_playerManager->getCurrentPlayer())[ecs::AComponent::ComponentType::ARMOR]);

			m_graphicModule->getHUD()->setBulletsNbr(weaponManager->getCurrentWeapon().getAmmunitionsClip());
			if (life != nullptr)
				m_graphicModule->getHUD()->setHealthPoint(life->get());
			else
				m_graphicModule->getHUD()->setHealthPoint(0);
			if (armor != nullptr)
				m_graphicModule->getHUD()->setArmorPoint(armor->get());
			else
				m_graphicModule->getHUD()->setArmorPoint(0);

			m_graphicModule->getHUD()->setTeam1Score(m_playerManager->getTeam1Score());
			m_graphicModule->getHUD()->setTeam2Score(m_playerManager->getTeam2Score());
			m_graphicModule->getHUD()->setPredatorScore(m_playerManager->getPredatorScore());
		}
		auto begin = std::chrono::high_resolution_clock::now();
		float elapsed = fpTime(begin - m_lastTime).count();
		CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(elapsed);
		m_lastTime = begin;
		if (!m_graphicModule->getMenuPause()->getEnableStatus() &&
			m_playerManager->getCurrentPlayer() &&
			(*m_playerManager->getCurrentPlayer())[ecs::AComponent::ComponentType::SCENE] != nullptr &&
			dynamic_cast<ecs::AScene*>((*m_playerManager->getCurrentPlayer())[ecs::AComponent::ComponentType::SCENE])->getNode() != nullptr)
		{
			Target::getInstance().refresh();
			ecs::PositionSystem::update(*m_playerManager->getCurrentPlayer());
			ecs::EventSystem::doEvents(*m_playerManager->getCurrentPlayer());
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
	ecs::Position mapPosition(irr::core::vector3df(-1350, -130, -1400), irr::core::vector3df(0.0, 0.0, 0.0));
	m_map = MapFactory::createMap(m_graphicModule->getDevice(), mapPosition, 1, "20kdm2.bsp", "map-20kdm2.pk3");
	ecs::PositionSystem::updateScenePosition(*m_map);
	if (ProjectGlobals::NO_MENU)
	{
		//Player 1
		ecs::Position playerPosition1(irr::core::vector3df(-1350, -130, -1400), irr::core::vector3df(0.0, 0.0, 0.0));
		m_player = PlayerFactory::createPlayer(m_graphicModule->getDevice(), "sydney.bmp", "sydney.md2", 2, playerPosition1, ecs::Team::TeamType::Team1, 100);
		ecs::PositionSystem::updateScenePosition(*m_player);
		m_playerManager->setCurrentPlayer(m_player);

		m_playerManager->initPlayersWeapons();
	}
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

MasterListNetwork*		ClientCore::getMasterList() const
{
	return m_masterList;
}

ecs::ClientId	ClientCore::getClientId()	const
{
	return m_clientId;
}

ecs::Entity* ClientCore::getMap() const
{
	return m_map;
}


void	ClientCore::setIsActive(bool isActive)
{
	m_isActive = isActive;
}

void	ClientCore::setNickname(const std::string& nickname)
{
	m_nickname = nickname;
	if (m_networkModule->getConnectionState() == RakNet::ConnectionState::IS_CONNECTED)
		m_networkModule->callRPC(NetworkRPC::PLAYER_MANAGER_SET_PLAYER_NICKNAME, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::PlayerManager), RakNet::RakString(nickname.c_str()));
}



void	ClientCore::setClientId(ecs::ClientId clientId, RakNet::RPC3* rpc)
{
	RakNet::RakString	nickname = m_nickname.c_str();

	m_clientId = clientId;
	LOG_INFO(NETWORK) << "Server accepted connection, clientId = " << m_clientId << ".";
	m_networkModule->callRPC(NetworkRPC::PLAYER_MANAGER_SET_PLAYER_NICKNAME, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::PlayerManager), nickname);
	LOG_DEBUG(NETWORK) << "Sent nickname \"" << nickname << "\" to server";
}

void	ClientCore::notifyInvalidNickname(RakNet::RPC3* rpc)
{
	LOG_INFO(NETWORK) << "Nickname already taken.";
	m_graphicModule->getWaitingRoom()->hide();
	m_graphicModule->getMainMenu()->display();
	m_graphicModule->getConnectWindow()->display();
	m_graphicModule->getConnectWindow()->disableConnectionStateCheck();
	m_graphicModule->getConnectWindow()->setStatus("Nickname already Taken");
}

void	ClientCore::startGame(RakNet::RPC3* rpc)
{
	m_graphicModule->getMainMenu()->hide();
	m_graphicModule->getHUD()->display();
	m_playerManager->initPlayersScene();
	m_graphicModule->setFPSCamera();
	m_graphicModule->getHUD()->timerStart();
	ClientCore::getInstance().createEntities();
	m_playerManager->initPlayersWeapons();
	LOG_INFO(GENERAL) << "Starting game.";
}

void ClientCore::onMessageRPC(RakNet::RakString str, unsigned int time, RakNet::RPC3* rpc)
{
	LOG_DEBUG(GENERAL) << "Message received";
	m_graphicModule->getHUD()->displayNotification(str.C_String(), time);
}