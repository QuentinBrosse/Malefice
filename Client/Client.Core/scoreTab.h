#pragma once

#include <irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/System.h>
#include <iostream>

class GraphicUtil;

class scoreTab
{
public:
	scoreTab(GraphicUtil &);
	~scoreTab() = default;
	void display();
	void hide();
	void addScoreRightTeam(const std::string &, unsigned int);
	void addScoreLeftTeam(const std::string &, unsigned int);
	void addScorePredatorTeam(const std::string &, unsigned int);
	void resetLists();
	bool onMainMenuButtonClicked(const CEGUI::EventArgs& e);
	bool onQuitButtonClicked(const CEGUI::EventArgs& e);
	bool onMainMenuButtonEnterArea(const CEGUI::EventArgs& e);
	bool onQuitButtonEnterArea(const CEGUI::EventArgs& e);
private:
	GraphicUtil&				m_graphicalUtil;
	CEGUI::Window*				m_windows;
	CEGUI::System&				m_systemd;
	CEGUI::Listbox*				m_rightTeam;
	CEGUI::Listbox*				m_leftTeam;
	CEGUI::Listbox*				m_predator;
	CEGUI::Window*				m_teamRight;
	CEGUI::Window*				m_teamLeft;
	CEGUI::Window*				m_teamPredator;
	unsigned int				m_rightTeamScore;
	unsigned int				m_leftTeamScore;
	unsigned int				m_predatorTeamScore;
};