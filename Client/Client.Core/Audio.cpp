#include "Audio.h"
#include "Logger.h"


Audio::Audio() :
	m_soundPath("Media/Sounds/"), m_isDeaf(false)
{
	m_sounds.insert(std::make_pair(SoundType::GUI_BTN_HOVER, m_soundPath + "gui_hover.wav"));
	m_sounds.insert(std::make_pair(SoundType::GUI_BTN_PRESS, m_soundPath + "gui_press.wav"));

	m_engine = irrklang::createIrrKlangDevice();
	LOG_DEBUG(GENERAL) << "MT : " << m_engine->isMultiThreaded();
}

Audio::~Audio()
{
	m_engine->drop();
}

void Audio::refreshListenerPosition(const ecs::Position& position)
{
	m_engine->setListenerPosition(
		irrklang::vec3df(position.getVectorPosition().X,
			position.getVectorPosition().Y,
			position.getVectorPosition().Z),
		irrklang::vec3df(position.getVectorRotation().X,
			position.getVectorRotation().Y,
			position.getVectorRotation().Z)
		);
}

void	Audio::playGUISound(const Audio::SoundType soundType)
{
	m_engine->play2D(m_sounds[soundType].c_str());
}

irrklang::ISound *	Audio::play2D(const std::string& soundFile, bool status)
{
	if (!m_isDeaf)
		return (m_engine->play2D((m_soundPath + soundFile).c_str(), status));
}

void Audio::play3D(const std::string& soundFile, const ecs::Position& position)
{
	if (!m_isDeaf)
	{
		irrklang::vec3df irrPos(position.getVectorPosition().X,
			position.getVectorPosition().Y,
			position.getVectorPosition().Z);
		m_engine->play3D((m_soundPath + soundFile).c_str(), irrPos);
	}
}

void Audio::setIsDeaf(const bool isDeaf)
{
	m_isDeaf = isDeaf;
}

bool Audio::isDeaf() const
{
	return m_isDeaf;
}

void Audio::playMenuSound()
{
	m_menuSound = m_engine->play2D((m_soundPath + "mainMenu.ogg").c_str(), true, false, false, irrklang::ESM_AUTO_DETECT, true);
}

void Audio::stopMenuSound()
{
	if (m_menuSound)
		m_menuSound->stop();
	else
		LOG_DEBUG(GENERAL) << "Cannot complie, m_menuSound is nullptr";
}