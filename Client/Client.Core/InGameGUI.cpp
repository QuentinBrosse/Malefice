#include "InGameGUI.h"
#include "Logger.h"

InGameGUI::InGameGUI() :
	m_hud(nullptr), m_systemd(CEGUI::System::getSingleton()), m_hpBar(nullptr), m_hpBarText(nullptr), m_timerText(nullptr), m_power1(nullptr), m_power2(nullptr), m_power3(nullptr), m_power4(nullptr), m_team1Score(nullptr), m_team2Score(nullptr), m_timestamp(0), m_hp(0), m_maxHP(100), m_stopTimer(true), m_power1Activated(false), m_power2Activated(false), m_power3Activated(false), m_power4Activated(false), m_maxPowerNbr(3), m_maxArmor(100), m_isActive(false)
{
	m_hud = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("InGameGUI.layout");
	m_hpBar = dynamic_cast<CEGUI::ProgressBar *>(m_hud->getChild(1));
	m_hpBarText = m_hud->getChild(2);
	m_hpBar->setProgress(0);
	m_hpBarText->setText(std::to_string(0));
	m_timerText = m_hud->getChild(100);

	m_power1 = m_hud->getChild(200)->getChild(201);
	m_power2 = m_hud->getChild(300)->getChild(301);
	m_power3 = m_hud->getChild(400)->getChild(401);
	m_power4 = m_hud->getChild(500)->getChild(501);
	m_powerList.push_back(m_power1);
	m_powerList.push_back(m_power2);
	m_powerList.push_back(m_power3);
	m_powerList.push_back(m_power4);

	m_team1Score = m_hud->getChild(50);
	m_team2Score = m_hud->getChild(51);
	m_predatorScore = m_hud->getChild(52);
	m_bullets = m_hud->getChild(600);
	m_armorBar = dynamic_cast<CEGUI::ProgressBar *>(m_hud->getChild(642));
	m_armors = m_hud->getChild(650);
	m_eventNotifier = dynamic_cast<CEGUI::Listbox *>(m_hud->getChild(1000));
}

void InGameGUI::display()
{
	m_systemd.getDefaultGUIContext().setRootWindow(m_hud);
	m_isActive = true;
}

void InGameGUI::hide()
{
	m_systemd.getDefaultGUIContext().setRootWindow(0);
	m_isActive = false;
}

void InGameGUI::addHealthPoint(unsigned int hp)
{
	long tmp = hp + this->m_hp;
	if (tmp > 0)
		this->m_hp += hp;
	else
		this->m_hp = 0;

	if (this->m_hp > this->m_maxHP)
		this->m_hp = this->m_maxHP;
	m_hpBar->setProgress(static_cast<float>(this->m_hp) / static_cast<float>(this->m_maxHP));
	m_hpBarText->setText(std::to_string(this->m_hp));
}

void InGameGUI::subHealthPoint(unsigned int hp)
{
	long tmp = hp - this->m_hp;
	if (tmp > 0)
		this->m_hp -= hp;
	else
		this->m_hp = 0;

	if (this->m_hp > this->m_maxHP)
		this->m_hp = this->m_maxHP;
	m_hpBar->setProgress(static_cast<float>(this->m_hp) / static_cast<float>(this->m_maxHP));
	m_hpBarText->setText(std::to_string(this->m_hp));
}

void InGameGUI::setHealthPoint(unsigned int hp)
{
	this->m_hp = hp;
	if (this->m_hp > this->m_maxHP)
		this->m_hp = this->m_maxHP;
	m_hpBar->setProgress(static_cast<float>(this->m_hp) / static_cast<float>(this->m_maxHP));
	m_hpBarText->setText(std::to_string(this->m_hp));
}

unsigned int InGameGUI::getHealthPoint()
{
	return (this->m_hp);
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

void InGameGUI::enablePower(int nbr)
{
	if (nbr >= 0 && nbr <= m_maxPowerNbr)
		m_powerList[nbr]->setProperty("Image", "Circles/GreenCircle");
	else
		std::cerr << "Given power number not exist" << std::endl;
}

void InGameGUI::disablePower(int nbr)
{
	if (nbr >= 0 && nbr <= m_maxPowerNbr)
		m_powerList[nbr]->setProperty("Image", "Circles/RedCircle");
	else
		std::cerr << "Given power number not exist" << std::endl;
}

void InGameGUI::setTeam1Score(int nbr)
{
	m_team1Score->setText(std::to_string(nbr));
}

void InGameGUI::setTeam2Score(int nbr)
{
	m_team2Score->setText(std::to_string(nbr));
}

void InGameGUI::setPredatorScore(int nbr)
{
	m_predatorScore->setText(std::to_string(nbr));
}

void InGameGUI::setBulletsNbr(unsigned int nbr)
{
	m_bullets->setText(std::to_string(nbr));
}

const bool InGameGUI::isActive() const
{
	return m_isActive;
}


void InGameGUI::addArmorPoint(unsigned int hp)
{
	long tmp = hp + this->m_armor;
	if (tmp > 0)
		this->m_armor += hp;
	else
		this->m_armor = 0;

	if (this->m_armor > this->m_maxArmor)
		this->m_armor = this->m_maxArmor;
	m_armorBar->setProgress(static_cast<float>(this->m_armor) / static_cast<float>(this->m_maxArmor));
	m_armors->setText(std::to_string(this->m_armor));
}

void InGameGUI::subArmorPoint(unsigned int hp)
{
	long tmp = hp - this->m_armor;
	if (tmp > 0)
		this->m_armor -= hp;
	else
		this->m_armor = 0;

	if (this->m_armor > this->m_maxArmor)
		this->m_armor = this->m_maxArmor;
	m_armorBar->setProgress(static_cast<float>(this->m_armor) / static_cast<float>(this->m_maxArmor));
	m_armors->setText(std::to_string(this->m_armor));
}

void InGameGUI::setArmorPoint(unsigned int hp)
{
	this->m_armor = hp;
	if (this->m_armor > this->m_maxArmor)
		this->m_armor = this->m_maxArmor;
	m_armorBar->setProgress(static_cast<float>(this->m_armor) / static_cast<float>(this->m_maxArmor));
	m_armors->setText(std::to_string(this->m_armor));
}

unsigned int InGameGUI::getArmorPoint()
{
	return (this->m_armor);
}

void InGameGUI::displayNotification(const std::string &notification, unsigned long duration)
{
	NotificationItemData *data = new NotificationItemData(duration);
	CEGUI::ListboxItem* item = new CEGUI::ListboxTextItem("item");
	item->setText("[colour='FFFF0000']"+ notification);
	item->setSelectionBrushImage("WindowsLook/TitlebarBottom");
	item->setSelected(false);
	item->setUserData(data);
	m_eventNotifier->addItem(item);
}

void InGameGUI::refreshEventDisplay()
{
	unsigned int count = m_eventNotifier->getItemCount();
	size_t idx = 0;
	while (idx < count && m_isActive)
	{
		try
		{
			CEGUI::ListboxItem* item = m_eventNotifier->getListboxItemFromIndex(idx);
			if (item != nullptr && item->getUserData() != nullptr)
			{
				NotificationItemData *data = reinterpret_cast<NotificationItemData *>(item->getUserData());
				if (data->getNotificationEndTimestamps() < time(nullptr))
				{
					m_eventNotifier->removeItem(item);
				}
			}
		}
		catch (std::exception &e)
		{
			LOG_DEBUG(GENERAL) << "Index Out of range Requested";
		}
		idx++;
	}
}

InGameGUI::NotificationItemData::NotificationItemData(unsigned long duration)
{
	m_begin = std::time(nullptr);
	m_end = m_begin + duration;
}

time_t InGameGUI::NotificationItemData::getNotificationEndTimestamps() const
{
	return m_end;
}