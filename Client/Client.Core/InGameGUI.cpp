#include "InGameGUI.h"

InGameGUI::InGameGUI()
{
	m_hud = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("InGameGUI.layout");
	m_hpBar = dynamic_cast<CEGUI::ProgressBar *>(m_hud->getChild(1));
	m_hpBarText = m_hud->getChild(2);
	m_hpBar->setProgress(0);
	m_hpBarText->setText(std::to_string(0) + "/" + std::to_string(this->max_hp));
	m_mpBarText = m_hud->getChild(10)->getChild(11);
	m_timerText = m_hud->getChild(100);
}

void InGameGUI::display()
{
	m_systemd.getDefaultGUIContext().setRootWindow(m_hud);
}

void InGameGUI::hide()
{
	m_systemd.getDefaultGUIContext().setRootWindow(0);
}

void InGameGUI::addHealthPoint(unsigned int hp)
{
	long tmp = hp + this->hp;
	if (tmp > 0)
		this->hp += hp;
	else
		this->hp = 0;

	if (this->hp > this->max_hp)
		this->hp = this->max_hp;
	m_hpBar->setProgress(static_cast<float>(this->hp) / static_cast<float>(this->max_hp));
	m_hpBarText->setText(std::to_string(this->hp));
}

void InGameGUI::subHealthPoint(unsigned int hp)
{
	long tmp = hp - this->hp;
	if (tmp > 0)
		this->hp -= hp;
	else
		this->hp = 0;

	if (this->hp > this->max_hp)
		this->hp = this->max_hp;
	m_hpBar->setProgress(static_cast<float>(this->hp) / static_cast<float>(this->max_hp));
	m_hpBarText->setText(std::to_string(this->hp));
}

void InGameGUI::setHealthPoint(unsigned int hp)
{
	this->hp = hp;
	if (this->hp > this->max_hp)
		this->hp = this->max_hp;
	m_hpBar->setProgress(static_cast<float>(this->hp) / static_cast<float>(this->max_hp));
	m_hpBarText->setText(std::to_string(this->hp));
}

unsigned int InGameGUI::getHealthPoint()
{
	return (this->hp);
}

void InGameGUI::addEnergyPoint(unsigned int mp)
{
	long tmp = mp + this->mp;
	if (tmp > 0)
		this->mp += mp;
	else
		this->mp = 0;

	if (this->mp > this->max_mp)
		this->mp = this->max_mp;
	m_mpBarText->setText(std::to_string(this->mp));
}

void InGameGUI::subEnergyPoint(unsigned int mp)
{
	long tmp = mp - this->mp;
	if (tmp > 0)
		this->mp -= mp;
	else
		this->mp = 0;

	if (this->mp > this->max_mp)
		this->mp = this->max_mp;
	m_mpBarText->setText(std::to_string(this->mp));
}

void InGameGUI::setEnergyPoint(unsigned int mp)
{
	this->mp = mp;
	if (this->mp > this->max_mp)
		this->mp = this->max_mp;
	m_mpBarText->setText(std::to_string(this->mp));
}

unsigned int InGameGUI::getEnergyPoint()
{
	return (this->mp);
}

void InGameGUI::timerStart()
{
	if (m_timestamp == 0)
		m_timestamp = std::time(nullptr);
	m_stopTimer = false;
}

void InGameGUI::timerStop()
{
	m_stopTimer = true;
}

void InGameGUI::timerReset()
{
	m_timestamp = std::time(nullptr);
}

void InGameGUI::refreshTime()
{
	if (!m_stopTimer)
	{
		std::time_t result = std::time(nullptr);
		std::string minute = std::to_string((result - m_timestamp) / 60);
		std::string seconde = std::to_string((result - m_timestamp) % 60);
		m_timerText->setText((minute.size() < 2 ? "0" + minute : minute) + ":" + (seconde.size() < 2 ? "0" + seconde : seconde));
	}
}