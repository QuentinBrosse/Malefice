#include "MenuPause.h"
#include "GraphicUtil.h"

MenuPause::MenuPause(GraphicUtil &utilities) : m_utilities(utilities), m_systemd(CEGUI::System::getSingleton()), m_windows(nullptr), m_isEnable(false), m_isActivated(false)
{
	m_windows = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("menuPause.layout");
	m_windows->setName("MenuPause");
	m_windows->getChild(1)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MenuPause::onContinueButtonClicked, this));
	m_windows->getChild(2)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MenuPause::onOptionButtonClicked, this));
	m_windows->getChild(3)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MenuPause::onQuitButtonClicked, this));

	m_windows->getChild(1)->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea, CEGUI::Event::Subscriber(&MenuPause::onContinueButtonEnterArea, this));
	m_windows->getChild(2)->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea, CEGUI::Event::Subscriber(&MenuPause::onOptionButtonEnterArea, this));
	m_windows->getChild(3)->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea, CEGUI::Event::Subscriber(&MenuPause::onQuitButtonEnterArea, this));

}

void MenuPause::display()
{
	m_systemd.getDefaultGUIContext().setRootWindow(m_windows);
	m_isEnable = true;
}

void MenuPause::hide()
{
	m_systemd.getDefaultGUIContext().setRootWindow(0);
	m_isEnable = false;
}

void MenuPause::checkPause()
{
	static bool block;

	if (m_isActivated)
	{
		if (m_utilities.getCEGUIEventReceiver().getKeyStateList()[irr::KEY_ESCAPE] == true && block)
			return;
		if (m_utilities.getCEGUIEventReceiver().getKeyStateList()[irr::KEY_ESCAPE] == true && !m_isEnable && !block)
		{
			m_isEnable = true;
			m_utilities.setGuiCamera();
			this->display();
			block = true;
		}
		else if (m_utilities.getCEGUIEventReceiver().getKeyStateList()[irr::KEY_ESCAPE] == true && m_isEnable && !block)
		{
			this->onContinueButtonClicked();
			block = true;
		}
		else if (m_utilities.getCEGUIEventReceiver().getKeyStateList()[irr::KEY_ESCAPE] == false && block)
			block = false;
	}
}

bool MenuPause::onOptionButtonClicked()
{
	m_utilities.getMenuOptions()->display();
	return (true);
}

bool MenuPause::onQuitButtonClicked()
{
	std::exit(0);
	return (true);
}

bool MenuPause::onContinueButtonClicked()
{
	m_utilities.setFPSCamera();
	this->hide();
	m_utilities.getHUD()->display();
	m_isEnable = false;
	return (true);
}

bool MenuPause::getEnableStatus()
{
	return (m_isEnable);
}

void MenuPause::activate(bool stat)
{
	m_isActivated = stat;
}

bool MenuPause::onContinueButtonEnterArea(const CEGUI::EventArgs& e)
{

	return true;
}

bool MenuPause::onOptionButtonEnterArea(const CEGUI::EventArgs& e)
{

	return true;
}

bool MenuPause::onQuitButtonEnterArea(const CEGUI::EventArgs& e)
{

	return true;
}