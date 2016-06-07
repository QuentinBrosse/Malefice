#include "TouchedFx.h"

TouchedFx::TouchedFx() : m_systemd(CEGUI::System::getSingleton()), m_isDisplayed(false), m_delay(100), m_time(0)
{
	m_windows = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("touchedFx.layout");
	m_isDisplayed = false;
}

void TouchedFx::display()
{
	m_isDisplayed = true;
	m_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	if (m_systemd.getDefaultGUIContext().getRootWindow() == nullptr)
	{
		m_systemd.getDefaultGUIContext().setRootWindow(m_windows);
	}
	else
	{
		m_systemd.getDefaultGUIContext().getRootWindow()->addChild(m_windows);
	}
}

void TouchedFx::hide()
{
	m_isDisplayed = false;
	try {
		if (m_systemd.getDefaultGUIContext().getRootWindow()->getChild(m_windows->getID()))
		{
			m_systemd.getDefaultGUIContext().getRootWindow()->removeChild(m_windows->getID());
		}
	}
	catch (std::exception &e)
	{

	}
}

void TouchedFx::refresh()
{
	std::chrono::milliseconds time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

	if ((time - m_time) >= m_delay && m_isDisplayed)
	{
		this->hide();
		m_isDisplayed = false;
		m_time = time;
	}
}
