#include "MenuOptions.h"

MenuOptions::MenuOptions(GraphicUtil &gu) : m_systemd(CEGUI::System::getSingleton()), m_utilities(gu)
{
	m_windows = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("options.layout");
	try
	{
		m_frameWindows = dynamic_cast<CEGUI::FrameWindow *>(m_windows);
		if (m_windows == nullptr)
			std::cout << "" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Failure while loading Frame windows:" << std::endl << std::endl;
		std::cout << e.what() << std::endl;
	}
	m_frameWindows->getCloseButton()->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MenuOptions::onCloseButtonClicked, this));
	m_windows->getChild(1)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MenuOptions::onCloseButtonClicked, this));
	m_windows->getChild(2)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MenuOptions::onCloseButtonClicked, this));
}

void MenuOptions::display()
{
	if (m_systemd.getDefaultGUIContext().getRootWindow() == nullptr)
	{
		std::cout << "Root Windows not found setting loading windows as root..." << std::endl;
		m_systemd.getDefaultGUIContext().setRootWindow(m_windows);
	}
	else
		m_systemd.getDefaultGUIContext().getRootWindow()->addChild(m_windows);
}

void MenuOptions::hide()
{
	try {
		m_systemd.getDefaultGUIContext().getRootWindow()->getChild(33);
		m_systemd.getDefaultGUIContext().getRootWindow()->removeChild(33);
	}
	catch (std::exception &e) {
		std::cout << "Root windows not found. hiding loading windows as Root Windows" << std::endl;
		m_systemd.getDefaultGUIContext().setRootWindow(0);
	}
}

bool MenuOptions::onCloseButtonClicked()
{
	this->hide();
	return (true);
}