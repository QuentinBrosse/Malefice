#include <iostream>
#include <queue>
#include "ServerCore.h"
#include "ProjectGlobals.h"
#include "ServerCoreConfiguration.h"
#include "Logger.h"

#include "Thread.h"
#include "Mutex.h"
#include "Utilities.h"

Thread					inputThread;
Mutex					consoleInputQueueMutex;
std::queue<std::string>	consoleInputQueue;
unsigned long			startTime;

void InputThread(Thread * creator)
{
	char		inputBuffer[512];
	std::string input;

	while (creator->getUserData<bool>())
	{
		fgets(inputBuffer, sizeof(inputBuffer), stdin);
		if (inputBuffer[0] != '\n')
		{
			input.append(inputBuffer);
			size_t sLength = input.length();

			if (input[sLength - 1] == '\n')
			{
				// Check for CRLF
				if (input[sLength - 2] == '\r')
					input.erase(sLength - 2, std::string::npos);
				else
					input.erase(sLength - 1, std::string::npos);

				consoleInputQueueMutex.lock();
				consoleInputQueue.push(input);
				consoleInputQueueMutex.unlock();

				input.clear();
			}
		}
		Sleep(10);
	}
}

void ConsoleInput(std::string input)
{
	if (input.empty())
		return;

	size_t s = input.find(" ", 0);
	std::string strCommand = input.substr(0, s++);
	std::string strParams = input.substr(s, (input.length() - s));

	ServerCore::getInstance().processCommand(strCommand, strParams);
}


ServerCore::ServerCore() :
	m_configuration(), m_networkModule(nullptr), m_isActive(true)
{
}


void	ServerCore::run()
{
	LOG_INFO(GENERAL) << "Server started.";
	if (this->init() == false)
	{
		LOG_CRITICAL(GENERAL) << "Server initialization failed. Abortring.";
		return;
	}
	LOG_INFO(GENERAL) << "Server initialized.";
	while (this->isActive())
	{
		this->pulse();
		if (consoleInputQueueMutex.tryLock(0))
		{
			while (!consoleInputQueue.empty())
			{
				ConsoleInput(consoleInputQueue.back().c_str());
				consoleInputQueue.pop();
			}
			consoleInputQueueMutex.unlock();
		}
	}
	this->stop();
	LOG_INFO(GENERAL) << "Server stopped.";
}

bool	ServerCore::init()
{
	if (m_configuration.loadFromFile(ServerCoreConfiguration::DEFAULT_SETTINGS_FILENAME) == false)
		return false;
	m_networkModule = new NetworkModule();
	if (m_networkModule->init(m_configuration.getAddress(), m_configuration.getPort(), m_configuration.getPassword()) == false)
	{
		LOG_CRITICAL(NETWORK) << "Failed to start Network Module.";
		return false;
	}

	inputThread.setUserData<bool>(true);
	inputThread.start(InputThread);
	startTime = Utilities::GetTime();

	this->displayHeader();
	return true;
}

void	ServerCore::stop()
{
	inputThread.setUserData<bool>(false);
	inputThread.stop(false, true);
}

void	ServerCore::pulse()
{
	if (m_networkModule != nullptr)
		m_networkModule->pulse();
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
	std::cout << "=Server Port	: " << m_configuration.getPort() << std::endl;
	std::cout << "=Max Players	: " << ProjectGlobals::MAX_PLAYERS_NB << std::endl;
	if(m_configuration.getPassword().length() > 0)
		std::cout << "=Password	: " << m_configuration.getPassword() << std::endl;
	std::cout << "==============================================================" << std::endl;

}

void	ServerCore::processCommand(const std::string& command, const std::string& params)
{
	if (command == "exit" || command == "quit" || command == "shutdown")
	{
		this->setIsActive(false);
	}
	else if (command == "uptime")
	{
		LOG_INFO(GENERAL) << "Current uptime : " << Utilities::GetTimePassedFromTime(startTime);
	}
}

bool	ServerCore::isActive()	const
{
	return m_isActive;
}

NetworkModule	*ServerCore::getNetworkModule()	const
{
	return m_networkModule;
}


void	ServerCore::setIsActive(bool isActive)
{
	m_isActive = isActive;
}
