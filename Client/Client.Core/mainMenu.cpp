#include "MainMenu.h"
#include "ClientCore.h"

MainMenu::MainMenu(GraphicUtil &gu) :
	m_windows(nullptr), m_systemd(CEGUI::System::getSingleton()), m_keyMap(nullptr), m_device(nullptr), m_driver(nullptr), m_sceneManager(nullptr), m_graphicUtils(gu)
{
	m_windows = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("mainMenu.layout");
	m_windows->setName("MainMenu");
	m_windows->getChild(2)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenu::onPlayButtonClicked, this));
	m_windows->getChild(1)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenu::onOptionButtonClicked, this));
	m_windows->getChild(0)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenu::onQuitButtonClicked, this));

	m_windows->getChild(2)->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea, CEGUI::Event::Subscriber(&MainMenu::onPlayButtonMouseEntersArea, this));
	m_windows->getChild(1)->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea, CEGUI::Event::Subscriber(&MainMenu::onOptionButtonMouseEntersArea, this));
	m_windows->getChild(0)->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea, CEGUI::Event::Subscriber(&MainMenu::onQuitButtonMouseEntersArea, this));

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
	m_graphicUtils.getMasterList()->display();
	return true;
}

bool MainMenu::onOptionButtonClicked(const CEGUI::EventArgs& e)
{
	m_graphicUtils.getMenuOptions()->display();
	return false;
}

bool MainMenu::onQuitButtonClicked(const CEGUI::EventArgs& e)
{
	ClientCore::getInstance().setIsActive(false);
	return false;
}

bool MainMenu::onPlayButtonMouseEntersArea(const CEGUI::EventArgs& e)
{

	return true;
}

bool MainMenu::onOptionButtonMouseEntersArea(const CEGUI::EventArgs& e)
{

	return true;
}

bool MainMenu::onQuitButtonMouseEntersArea(const CEGUI::EventArgs& e)
{
	
	return true;
}