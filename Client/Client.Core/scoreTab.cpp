#include "scoreTab.h"
#include "GraphicUtil.h"
#include "Audio.h"

scoreTab::scoreTab(GraphicUtil &gu) : m_systemd(CEGUI::System::getSingleton()), m_graphicalUtil(gu)
{
	m_windows = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("scoreTab.layout");
	m_rightTeam = dynamic_cast<CEGUI::Listbox *>(m_windows->getChild(40));
	m_leftTeam = dynamic_cast<CEGUI::Listbox *>(m_windows->getChild(41));
	m_predator = dynamic_cast<CEGUI::Listbox *>(m_windows->getChild(42));
	m_teamLeft = m_windows->getChild(51);
	m_teamRight = m_windows->getChild(50);
	m_teamPredator = m_windows->getChild(53);
	m_rightTeamScore = 0;
	m_leftTeamScore = 0;
	m_predatorTeamScore = 0;

	m_windows->getChild(1)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&scoreTab::onMainMenuButtonClicked, this));
	m_windows->getChild(2)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&scoreTab::onQuitButtonClicked, this));

	m_windows->getChild(1)->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea, CEGUI::Event::Subscriber(&scoreTab::onMainMenuButtonEnterArea, this));
	m_windows->getChild(2)->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea, CEGUI::Event::Subscriber(&scoreTab::onQuitButtonEnterArea, this));
}

void scoreTab::display()
{
	m_systemd.getDefaultGUIContext().setRootWindow(m_windows);
	Audio::getInstance().stopGameSound();
	Audio::getInstance().playGameEndSound();
}

void scoreTab::hide()
{
	m_systemd.getDefaultGUIContext().setRootWindow(0);
}

void scoreTab::addScoreRightTeam(const std::string &name, unsigned int score)
{
	m_rightTeamScore += score;
	m_teamRight->setText(std::string("Equipe 1: ") + std::to_string(m_rightTeamScore));
	CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem("default");
	item->setText(name + ": " + std::to_string(score));
	m_rightTeam->addItem(item);
}

void scoreTab::addScoreLeftTeam(const std::string &name, unsigned int score)
{
	m_leftTeamScore += score;
	m_teamLeft->setText(std::string("Equipe 2: ") + std::to_string(m_leftTeamScore));
	CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem("default");
	item->setText(name + ": " + std::to_string(score));
	m_leftTeam->addItem(item);
}

void scoreTab::addScorePredatorTeam(const std::string &name, unsigned int score)
{
	m_predatorTeamScore += score;
	m_teamPredator->setText(std::string("Predator : ") + std::to_string(m_predatorTeamScore));
	CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem("default");
	item->setText(name + ": " + std::to_string(score));
	m_predator->addItem(item);
}

void scoreTab::resetLists()
{
	m_rightTeamScore = 0;
	m_leftTeamScore = 0;
	m_predatorTeamScore = 0;
	m_leftTeam->resetList();
	m_rightTeam->resetList();
	m_leftTeam->resetList();
}

bool scoreTab::onMainMenuButtonClicked(const CEGUI::EventArgs& e)
{
	Audio::getInstance().stopGameEndSound();
	this->hide();
	m_graphicalUtil.getMainMenu()->display();
	Audio::getInstance().playMenuSound();
	return true;
}

bool scoreTab::onQuitButtonClicked(const CEGUI::EventArgs& e)
{
	std::exit(0);
	return true;
}

bool scoreTab::onMainMenuButtonEnterArea(const CEGUI::EventArgs& e)
{
	return true;
}

bool scoreTab::onQuitButtonEnterArea(const CEGUI::EventArgs& e)
{
	return true;
}