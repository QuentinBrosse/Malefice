#include "MainMenu.h"
#include "ClientCore.h"

MainMenu::MainMenu(GraphicUtil &gu) :
	m_windows(nullptr), m_systemd(CEGUI::System::getSingleton()), m_keyMap(nullptr), m_device(nullptr), m_driver(nullptr), m_sceneManager(nullptr), m_graphicUtils(gu)
{
	m_windows = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("mainMenu.layout");
	m_windows->getChild(0)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenu::onQuitButtonClicked, this));
	m_windows->getChild(2)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenu::onPlayButtonClicked, this));
}

void MainMenu::display()
{
	m_systemd.getDefaultGUIContext().setRootWindow(m_windows);
}

void MainMenu::hide()
{
	m_systemd.getDefaultGUIContext().setRootWindow(0);
}

bool MainMenu::onPlayButtonClicked(const CEGUI::EventArgs& e)
{
	m_graphicUtils.getConnectWindow()->display();
	return (true);
}

bool MainMenu::onOptionButtonClicked(const CEGUI::EventArgs& e)
{
	return (false);
}

bool MainMenu::onQuitButtonClicked(const CEGUI::EventArgs& e)
{
	ClientCore::getInstance().setIsActive(false);
	return (false);
}