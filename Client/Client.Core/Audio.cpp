#include "Audio.h"
#include "Logger.h"

Audio::Audio() :
	m_soundPath("Media/Sounds/")
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

void	Audio::play2D(const std::string& soundFile)
{
	m_engine->play2D((m_soundPath + soundFile).c_str());
}

void Audio::play3D(const std::string& soundFile, const ecs::Position& position)
{
	irrklang::vec3df irrPos(position.getVectorPosition().X,
		position.getVectorPosition().Y,
		position.getVectorPosition().Z);
	m_engine->play3D((m_soundPath + soundFile).c_str(), irrPos);
}
