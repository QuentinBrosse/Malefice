#include "Blind.h"
#include "Logger.h"
#include <iomanip>


Blind::Blind() : m_alpha(0), m_delay(10), m_maxAplha(255), m_windows(nullptr), m_systemd(CEGUI::System::getSingleton()), m_time(0), m_step(1), m_isDisplayed(false)
{
	m_windows = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("blind.layout");
	m_windows->setProperty("BackgroundColours", "tl:00000000 tr:00000000 bl:00000000 br:00000000");
}

void Blind::display()
{
	m_isDisplayed = true;
	if (m_systemd.getDefaultGUIContext().getRootWindow() == nullptr)
	{
		m_systemd.getDefaultGUIContext().setRootWindow(m_windows);
	}
	else
	{
		m_systemd.getDefaultGUIContext().getRootWindow()->addChild(m_windows);
	}
}

void Blind::hide()
{
	m_isDisplayed = false;
	m_alpha = 0;
	m_windows->setProperty("BackgroundColours", "tl:00000000 tr:00000000 bl:00000000 br:00000000");
	try {
		if (m_systemd.getDefaultGUIContext().getRootWindow()->getChild(4242))
		{
			m_systemd.getDefaultGUIContext().getRootWindow()->removeChild(4242);
		}
	}
	catch (std::exception &e)
	{
		m_systemd.getDefaultGUIContext().setRootWindow(0);
	}
}

void Blind::refresh()
{
	std::chrono::milliseconds time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

	if ((time - m_time) >= m_delay && m_isDisplayed && m_alpha < m_maxAplha)
	{
		std::cout << "Time: " << time.count() << " m_time: " << m_time.count() << " Delay:" << m_delay.count() << " m_aplha: " << m_alpha << std::endl;
		m_alpha += m_step;
		std::stringstream stream;
		stream << std::hex << m_alpha;
		std::string hexa(stream.str());
		m_windows->setProperty("BackgroundColours", "tl:" + hexa + "000000 tr:" + hexa + "000000 bl:" + hexa + "000000 br:" + hexa + "000000");
		m_time = time;
	}
}