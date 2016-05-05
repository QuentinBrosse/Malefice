#pragma once

#include <string>
#include <irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/System.h>
#include <ctime>
#include <vector>
#include <iostream>

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
	void enablePower(int nbr);
	void disablePower(int nbr);
	void setTeam1Score(int nbr);
	void setTeam2Score(int nbr);
private:
	CEGUI::Window* m_hud;
	CEGUI::System& m_systemd = CEGUI::System::getSingleton();
	CEGUI::ProgressBar* m_hpBar;
	CEGUI::Window* m_hpBarText;
	CEGUI::Window* m_mpBarText;
	CEGUI::Window* m_timerText;
	CEGUI::Window* m_power1;
	CEGUI::Window* m_power2;
	CEGUI::Window* m_power3;
	CEGUI::Window* m_power4;
	CEGUI::Window* m_team1_score;
	CEGUI::Window* m_team2_score;

	std::time_t m_timestamp = 0;

	std::vector<CEGUI::Window*> m_powerList;

	unsigned int hp = 0;
	unsigned int mp = 0;
	const unsigned int max_hp = 100;
	const unsigned int max_mp = 150;
	bool m_stopTimer = true;

	bool m_power1_activated;
	bool m_power2_activated;
	bool m_power3_activated;
	bool m_power4_activated;

	const int m_maxPowerNbr = 3;
};