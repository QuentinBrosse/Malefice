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
	void addArmorPoint(unsigned int);
	void subArmorPoint(unsigned int);
	void setArmorPoint(unsigned int);
	unsigned int getArmorPoint();
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
	void setPredatorScore(int nbr);
	void setBulletsNbr(unsigned int nbr);
	const bool isActive() const;
	void displayNotification(const std::string &, unsigned long = 3);
	void refreshEventDisplay();
	void setPowerVisible(int, bool);

private:
	CEGUI::Window* m_hud;
	CEGUI::System& m_systemd;
	CEGUI::ProgressBar* m_hpBar;
	CEGUI::Window* m_hpBarText;
	CEGUI::Window* m_timerText;
	CEGUI::Window* m_power1;
	CEGUI::Window* m_power2;
	CEGUI::Window* m_power3;
	CEGUI::Window* m_power4;
	CEGUI::Window* m_team1Score;
	CEGUI::Window* m_team2Score;
	CEGUI::Window* m_predatorScore;
	CEGUI::Window* m_bullets;
	CEGUI::Window* m_armors;
	CEGUI::Listbox* m_eventNotifier;
	CEGUI::ProgressBar* m_armorBar;
	std::time_t m_timestamp;
	std::vector<CEGUI::Window*> m_powerList;
	unsigned int m_hp;
	unsigned int m_armor;
	const unsigned int m_maxHP;
	const unsigned int m_maxArmor;
	bool m_stopTimer;
	bool m_isActive;
	bool m_power1Activated;
	bool m_power2Activated;
	bool m_power3Activated;
	bool m_power4Activated;
	const int m_maxPowerNbr;

	class NotificationItemData
	{
	public:
		NotificationItemData(unsigned long);
		~NotificationItemData() = default;
		time_t getNotificationEndTimestamps() const;
	private:
		time_t m_begin;
		time_t m_end;
	};
};