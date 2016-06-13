#include <chrono>
#include <irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Irrlicht/Renderer.h>
#include <utility>
#include <map>
#include "ClientCore.h"
#include "ProjectGlobals.h"
#include "GraphicUtil.h"
#include "Logger.h"
#include "NodePickable.h"
#include "MapFactory.h"
#include "PlayerFactory.h"
#include "SpawnerFactory.h"
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
#include "SpellSystem.h"
#include "TouchedFx.h"

ClientCore::ClientCore() : Singleton<ClientCore>(), NetworkObject(NetworkRPC::ReservedNetworkIds::ClientCore),
	m_networkModule(nullptr), m_graphicModule(nullptr), m_playerManager(nullptr), m_spawnerManager(nullptr), m_masterList(nullptr), m_clientId(), m_isActive(true), m_map(nullptr), m_player(nullptr), m_player_ia(nullptr)
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
	m_graphicModule->setGuiCamera();
	m_graphicModule->getMainMenu()->display();
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
	m_audioModule = &Audio::getInstance();
	m_playerManager = &PlayerManager::getInstance();
	m_spawnerManager = &SpawnerManager::getInstance();
	return true;

}

void	ClientCore::pulse()
{
	if (m_networkModule != nullptr && (m_networkModule->getConnectionState() == RakNet::ConnectionState::IS_CONNECTED || m_networkModule->getConnectionState() == RakNet::ConnectionState::IS_CONNECTING))
		m_networkModule->pulse();

	if (m_graphicModule->getDevice()->isWindowActive())
	{
		m_graphicModule->getDevice()->setEventReceiver(&m_graphicModule->getCEGUIEventReceiver());
		m_graphicModule->getMenuPause()->checkPause();
		m_graphicModule->getWaitingRoom()->refreshTime();
		m_graphicModule->getHUD()->refreshTime();
		m_graphicModule->getConnectWindow()->checkConnectionStatus();
		m_graphicModule->getWaitingRoom()->checkConnectedPlayers();
		m_graphicModule->getHUD()->refreshEventDisplay();
		m_graphicModule->getBlindFx()->refresh();
		m_graphicModule->getTouchedFx()->refresh();
		m_graphicModule->getDeadGUI()->refresh();

		if (m_graphicModule->getHUD()->isActive() && m_playerManager->getCurrentPlayer() != nullptr)
		{
			ecs::WeaponManager*	weaponManager = dynamic_cast<ecs::WeaponManager*>((*m_playerManager->getCurrentPlayer())[ecs::AComponent::ComponentType::WEAPON_MANAGER]);
			ecs::Life* life = dynamic_cast<ecs::Life*>((*m_playerManager->getCurrentPlayer())[ecs::AComponent::ComponentType::LIFE]);
			ecs::Armor* armor = dynamic_cast<ecs::Armor*>((*m_playerManager->getCurrentPlayer())[ecs::AComponent::ComponentType::ARMOR]);

			if (weaponManager)
			{
				m_graphicModule->getHUD()->setAmoClip(weaponManager->getCurrentWeapon().getAmmunitions());
				m_graphicModule->getHUD()->setBulletsNbr(weaponManager->getCurrentWeapon().getAmmunitionsClip());
			}
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
			Audio::getInstance().refreshListenerPosition(GraphicUtil::getInstance().getFPSCamera()->getPositionTarget());
			ecs::PositionSystem::update(*m_playerManager->getCurrentPlayer());
			ecs::EventSystem::doEvents(*m_playerManager->getCurrentPlayer());
			ecs::SpellSystem::affect(*m_playerManager->getCurrentPlayer());
			m_spawnerManager->collisionDetection(*m_playerManager->getCurrentPlayer());
			m_playerManager->initPlayersWeapons();
			m_playerManager->checkTexturesPredator();
		}
		m_graphicModule->getDriver()->beginScene(true, true, irr::video::SColor(255, 150, 150, 150));
		m_graphicModule->getSceneManager()->drawAll();
		CEGUI::System::getSingleton().renderAllGUIContexts();
		m_graphicModule->CEGUIEventInjector();
		m_graphicModule->getDriver()->endScene();
	}
}


void ClientCore::createEntities()
{
	ecs::Position mapPosition(irr::core::vector3df(-1350, -130, -1400), irr::core::vector3df(0.0, 0.0, 0.0));
	m_map = MapFactory::createMap(m_graphicModule->getDevice(), mapPosition, 1, "20kdm2.bsp", "map-20kdm2.pk3");
	ecs::PositionSystem::updateScenePosition(*m_map);
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
	Audio::getInstance().stopMenuSound();
	Audio::getInstance().playGameSound();
	m_graphicModule->getMenuPause()->activate(true);
	m_graphicModule->getMainMenu()->hide();
	m_graphicModule->getHUD()->display();
	m_playerManager->initPlayersScene();
	m_spawnerManager->initSpawnersScene();
	m_graphicModule->setFPSCamera();
	m_graphicModule->initSky();
	m_graphicModule->getHUD()->timerStart();
	this->createEntities();
	LOG_INFO(GENERAL) << "Starting game.";
}

void ClientCore::onMessageRPC(RakNet::RakString str, unsigned int time, RakNet::RPC3* rpc)
{
	LOG_DEBUG(GENERAL) << "Message received";
	m_graphicModule->getHUD()->displayNotification(str.C_String(), time);
}

void ClientCore::stopGame(RakNet::RPC3 * rpc)
{
	m_playerManager->setCurrentPlayer(nullptr);
	m_graphicModule->getMenuPause()->activate(false);
	m_graphicModule->setGuiCamera();
	//Ajouter le score ici

	std::map<std::string, std::pair<int, ecs::Team::TeamType>> scores = m_playerManager->getPlayersScore();

	for (auto it : scores)
	{
		if (it.second.second == ecs::Team::TeamType::Team1)
			m_graphicModule->getScoreTab()->addScoreRightTeam(it.first, it.second.first);
		else if (it.second.second == ecs::Team::TeamType::Team2)
			m_graphicModule->getScoreTab()->addScoreLeftTeam(it.first, it.second.first);
		else
			m_graphicModule->getScoreTab()->addScorePredatorTeam(it.first, it.second.first);
	}

	//Pour chaques joueurs
	m_graphicModule->getScoreTab()->display();

}
