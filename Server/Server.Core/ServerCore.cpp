#include <iostream>
#include <irrlicht.h>
#include "ServerCore.h"
#include "ProjectGlobals.h"
#include "Logger.h"
#include "TimeUtility.h"
#include "Position.h"
#include "PositionSystem.h"
#include "WeaponManager.h"
#include "WeaponManagerSystem.h"
#include "EventSystem.h"
#include "MapFactory.h"
#include "SpawnerFactory.h"
#include "NodePickable.h"
#include "SpawnerManager.h"

const unsigned int	ServerCore::ENTITIES_UPDATES_TICKS = 64;

ServerCore::ServerCore() :
	m_startTime(0), m_updateElapsedTime(0), m_isActive(false), m_gameStarted(false), m_configuration(), m_networkModule(), m_playerManager(), m_physicsUtil(PhysicsUtil::getInstance()), m_masterList(), m_queryServer(), m_inputQueue(), m_inputMutex(), m_readInput(), m_inputThread()
{
}


void	ServerCore::run()
{
	long long	lastTickTime = utility::TimeUtility::getMsTime();
	long long	currentTime = lastTickTime;

	LOG_INFO(GENERAL) << "Server started.";
	if (this->init() == false)
	{
		LOG_CRITICAL(GENERAL) << "Server initialization failed. Aborting.";
		return;
	}
	LOG_INFO(GENERAL) << "Server initialized.";
	while (m_isActive)
	{
		currentTime = utility::TimeUtility::getMsTime();
		this->pulse(currentTime - lastTickTime);
		lastTickTime = currentTime;
		this->handleInput();
	}
	this->stop();
	LOG_INFO(GENERAL) << "Server stopped.";
}

bool	ServerCore::init()
{
	if (m_configuration.loadFromFile(ServerCoreConfiguration::DEFAULT_SETTINGS_FILENAME) == false)
		return false;
	if (m_networkModule.init(m_configuration.getAddress(), m_configuration.getPort(), m_configuration.getPassword()) == false)
	{
		LOG_CRITICAL(NETWORK) << "Failed to start Network Module.";
		return false;
	}
	m_isActive = true;
	m_masterList.getInstance().run();
	m_queryServer.getInstance().init(m_configuration.getPort() + 1);
	m_readInput = true;
	m_inputThread = std::thread(&ServerCore::readInput, this);
	m_startTime = utility::TimeUtility::getMsTime();
	this->displayHeader();
	return true;
}

void	ServerCore::stop()
{
	m_readInput = false;
	m_inputThread.join();
}

void	ServerCore::displayHeader()	const
{
	std::string	title = ProjectGlobals::GAME_NAME + " v." + ProjectGlobals::GAME_SERVER_VERSION;

#ifdef WIN32
	SetConsoleTitle(title.c_str());
#endif

	std::cout << "==============================================================" << std::endl;
	std::cout << "                         " << title << std::endl;
	std::cout << "==============================================================" << std::endl;
	std::cout << "=Server Name	: " << m_configuration.getName() << std::endl;
	std::cout << "=Server bound to: " << m_configuration.getAddress() << std::endl;
	std::cout << "=Server Port	: " << m_configuration.getPort() << std::endl;
	std::cout << "=Max Players	: " << ProjectGlobals::MAX_PLAYERS_NB << std::endl;
	if (m_configuration.getPassword().length() > 0)
		std::cout << "=Password	: " << m_configuration.getPassword() << std::endl;
	std::cout << "==============================================================" << std::endl;

}


void	ServerCore::pulse(long long elapsedTime)
{
	m_updateElapsedTime += elapsedTime;
	m_networkModule.pulse();
	
	if (m_gameStarted == true && m_updateElapsedTime >= 1000.0 / ServerCore::ENTITIES_UPDATES_TICKS)
	{ 
		m_playerManager.updateEntities();
		m_spawnerManager.updateEntities();
		m_updateElapsedTime = 0;
	}
	m_physicsUtil.getVideoDriver()->beginScene();

	m_physicsUtil.getSceneManager()->drawAll();

	m_physicsUtil.getVideoDriver()->endScene();
}


void	ServerCore::readInput()
{
	while (m_readInput)
	{
		std::string	input;

		std::getline(std::cin, input);
		m_inputMutex.lock();
		m_inputQueue.push(input);
		m_inputMutex.unlock();
	}
}

void	ServerCore::handleInput()
{
	if (m_inputMutex.try_lock())
	{
		while (!m_inputQueue.empty())
		{
			std::string	input = m_inputQueue.back();
			std::size_t	paramsOffset = input.find(" ") + 1;
			std::string	command = input.substr(0, paramsOffset - 1);
			std::string	params = input.substr(paramsOffset);

			if (input.empty())
			{
				m_inputMutex.unlock();
				return;
			}
			this->processCommand(command, params);
			m_inputQueue.pop();
		}
		m_inputMutex.unlock();
	}
}

void	ServerCore::processCommand(const std::string& command, const std::string& params)
{
	if (command == "exit" || command == "quit" || command == "shutdown")
	{
		m_isActive = false;
		std::cout << "Press RETURN to close this window..." << std::endl;
	}
	else if (command == "uptime")
	{
		LOG_INFO(GENERAL) << "Current uptime: " << utility::TimeUtility::getElapsedTimeSince(m_startTime);
	}
}

void ServerCore::createEntities()
{
	ecs::Position	mapPos(irr::core::vector3df(-1350, -130, -1400), irr::core::vector3df(0, 0, 0));
	ecs::Entity*	map = MapFactory::createMap(m_physicsUtil.getDevice(), mapPos, -1, "20kdm2.bsp", "map-20kdm2.pk3");

	//Weapon Spawner
	m_spawnerManager.createEntity((ecs::ClientId)20);
	/*ecs::Position spawnPosition1(irr::core::vector3df(-10, -50, -70), irr::core::vector3df(0.0, 0.0, 0.0), irr::core::vector3df(800.f, 1000.f, 100.f));
	ecs::Entity*	spawnerWeapon1 = SpawnerFactory::createWeaponSpawner(m_physicsUtil.getInstance().getDevice(), spawnPosition1, 18);
	m_spawnerManager.addEntity(spawnerWeapon1->getOwner(), spawnerWeapon1);
	ecs::PositionSystem::initScenePosition(*spawnerWeapon1);*/
	for (auto& entity : m_spawnerManager.getSpawners())
	{
		ecs::PositionSystem::updateScenePosition(*entity.second);
	}
	ecs::PositionSystem::updateScenePosition(*map);
}

void	ServerCore::startGame()
{
	this->createEntities();
	ServerCore::getInstance().getNetworkModule().callRPC(NetworkRPC::CLIENT_CORE_START_GAME, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::ClientCore), RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
	m_gameStarted = true;
}

bool	ServerCore::isActive() const
{
	return m_isActive;
}

NetworkModule&	ServerCore::getNetworkModule()
{
	return m_networkModule;
}

PlayerManager&	ServerCore::getPlayerManager()
{
	return m_playerManager;
}

//SpawnerManager& ServerCore::getSpawnerManager()
//{
//	return m_spawnerManager;
//}

ServerCoreConfiguration& ServerCore::getServerCoreConfiguration()
{
	return m_configuration;
}

MasterList& ServerCore::getMasterList()
{
	return m_masterList;
}

PhysicsUtil& ServerCore::getPhysicsUtil()
{
	return m_physicsUtil;
}
