#include "ClientCore.h"
#include "ProjectGlobals.h"
#include "GraphicUtil.h"
#include "Logger.h"

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
	m_graphicModule = new GraphicUtil(irr::video::EDT_DIRECT3D9, irr::core::dimension2d<irr::u32>(1280, 720), ecs::Position(0, 0, 0, 0, 0, 0));
	if (m_graphicModule != nullptr)
		m_graphicModule->initGraphics();*/
}

void	ClientCore::pulse()
{
	if (m_networkModule != nullptr && m_networkModule->isConnected())
		m_networkModule->pulse();

	if (m_graphicModule->getDevice()->isWindowActive()) //draw only if the window is active
	{
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


void	ClientCore::setIsActive(bool isActive)
{
	m_isActive = isActive;
}
