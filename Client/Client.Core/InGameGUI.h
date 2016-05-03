#pragma once

#include <string>
#include <irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/System.h>
#include <ctime>

class InGameGUI
{
public:
	InGameGUI();
	~InGameGUI() = default;
	void addHealthPoint(unsigned int);
	void subHealthPoint(unsigned int);
	void setHealthPoint(unsigned int);
	unsigned int getHealthPoint();
	void addEnergyPoint(unsigned int);
	void subEnergyPoint(unsigned int);
	void setEnergyPoint(unsigned int);
	unsigned int getEnergyPoint();
	void display();
	void hide();
	void refreshTime();
	void timerStart();
	void timerReset();
	void timerStop();
private:
	CEGUI::Window* m_hud;
	CEGUI::System& m_systemd = CEGUI::System::getSingleton();
	CEGUI::ProgressBar* m_hpBar;
	CEGUI::Window* m_hpBarText;
	CEGUI::Window* m_mpBarText;
	CEGUI::Window* m_timerText;

	std::time_t m_timestamp = 0;

	unsigned int hp = 0;
	unsigned int mp = 0;
	const unsigned int max_hp = 100;
	const unsigned int max_mp = 150;
	bool m_stopTimer = true;

};