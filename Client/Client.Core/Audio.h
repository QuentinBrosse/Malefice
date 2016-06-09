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
	irrklang::ISound* play2D(const std::string& soundFile, bool = false);
	void	play3D(const std::string& soundFile, const ecs::Position& position);

	void	setIsDeaf(const bool isDeaf);

	bool	isDeaf()	const;

	void	playMenuSound();
	void	stopMenuSound();
	void	playGameSound();
	void	stopGameSound();
	void	playGameEndSound();
	void	stopGameEndSound();
protected:
	Audio();
	~Audio();

private:
	const std::string								m_soundPath;
	irrklang::ISoundEngine*							m_engine;
	std::map<const SoundType, const std::string>	m_sounds;
	irrklang::ISound*								m_menuSound;
	irrklang::ISound*								m_gameSound;
	irrklang::ISound*								m_gameEndSound;
	bool											m_isDeaf;
};