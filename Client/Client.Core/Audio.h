#pragma once
#include	<irrKlang.h>
#include	<string>
#include	<map>

#include	"Singleton.h"
#include	"Position.h"

class Audio : public Singleton<Audio>
{
	friend class Singleton<Audio>;

public:

	enum class SoundType : uint8_t
	{
		GUI_BTN_HOVER,
		GUI_BTN_PRESS,
		// GUI_BTN_RELEASE,
		COUNT
	};

	void	refreshListenerPosition(const ecs::Position& position);
	void	playGUISound(const SoundType);
	void	play2D(const std::string& soundFile);
	void	play3D(const std::string& soundFile, const ecs::Position& position);

protected:
	Audio();
	~Audio();

private:
	const std::string								m_soundPath;
	irrklang::ISoundEngine*							m_engine;
	std::map<const SoundType, const std::string>	m_sounds;

};