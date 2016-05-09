#include "MainMenu.h"


MainMenu::MainMenu(NetworkModule& networkModule) : m_systemd(CEGUI::System::getSingleton()), m_networkModule(networkModule), m_connectWindow(m_networkModule)
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
	m_connectWindow.display();
	return (true);
}

bool MainMenu::onOptionButtonClicked(const CEGUI::EventArgs& e)
{
	return (false);
}

bool MainMenu::onQuitButtonClicked(const CEGUI::EventArgs& e)
{
	std::cout << "Exiting..." << std::endl;
	exit(EXIT_SUCCESS);
	return (false);
}