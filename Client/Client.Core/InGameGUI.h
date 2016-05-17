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
	CEGUI::System& m_systemd;
	CEGUI::ProgressBar* m_hpBar;
	CEGUI::Window* m_hpBarText;
	CEGUI::Window* m_mpBarText;
	CEGUI::Window* m_timerText;
	CEGUI::Window* m_power1;
	CEGUI::Window* m_power2;
	CEGUI::Window* m_power3;
	CEGUI::Window* m_power4;
	CEGUI::Window* m_team1Score;
	CEGUI::Window* m_team2Score;
	std::time_t m_timestamp;
	std::vector<CEGUI::Window*> m_powerList;
	unsigned int m_hp;
	unsigned int m_mp;
	const unsigned int m_maxHP;
	const unsigned int m_maxMP;
	bool m_stopTimer;
	bool m_power1Activated;
	bool m_power2Activated;
	bool m_power3Activated;
	bool m_power4Activated;
	const int m_maxPowerNbr;
};