#include "ConnectWindow.h"
#include "ClientCore.h"

ConnectWindow::ConnectWindow(GraphicUtil &gu) :
	m_windows(nullptr), m_ip(nullptr), m_port(nullptr), m_systemd(CEGUI::System::getSingleton()), m_frameWindows(nullptr), m_ipStr(""), m_portStr(""), m_graphicUtils(gu)
{
	m_windows = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("connectWindows.layout");
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
	m_frameWindows->getCloseButton()->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ConnectWindow::onCloseButtonClicked, this));
	m_windows->getChild(3)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ConnectWindow::onConnectButtonClicked, this));
	m_ip = dynamic_cast<CEGUI::Editbox *>(m_windows->getChild(1));
	m_port = dynamic_cast<CEGUI::Editbox *>(m_windows->getChild(2));
	m_pseudo = dynamic_cast<CEGUI::Editbox *>(m_windows->getChild(3));
}

void ConnectWindow::display()
{
	if (m_systemd.getDefaultGUIContext().getRootWindow() == nullptr)
	{
		std::cout << "Root Windows not found setting loading windows as root..." << std::endl;
		m_systemd.getDefaultGUIContext().setRootWindow(m_windows);
	}
	else
		m_systemd.getDefaultGUIContext().getRootWindow()->addChild(m_windows);
}

void ConnectWindow::hide()
{
	try {
		m_systemd.getDefaultGUIContext().getRootWindow()->getChild(66);
		m_systemd.getDefaultGUIContext().getRootWindow()->removeChild(66);
	}
	catch (std::exception &e) {
		std::cout << "Root windows not found. hiding loading windows as Root Windows" << std::endl;
		m_systemd.getDefaultGUIContext().setRootWindow(0);
	}
}

bool ConnectWindow::onCloseButtonClicked(const CEGUI::EventArgs& e)
{
	this->hide();
	return (true);
}

bool ConnectWindow::onConnectButtonClicked(const CEGUI::EventArgs& e)
{
	if (this->getIPEditBox().length() > 0 && this->getPortEditBox().length() > 0) {
		ClientCore::getInstance().getNetworkModule()->connect(this->getIPEditBox(), std::stoi(this->getPortEditBox()), "");
		this->hide();
		m_systemd.getDefaultGUIContext().setRootWindow(0);
		m_graphicUtils.getWaitingRoom()->display();
		return true;
	} else {
		return false;
	}
}

std::string ConnectWindow::getIPEditBox()
{
	return (m_ip->getText().c_str());
}

std::string ConnectWindow::getPortEditBox()
{
	return (m_port->getText().c_str());
}

std::string ConnectWindow::getPseudoEditBox()
{
	return (m_pseudo->getText().c_str());
}