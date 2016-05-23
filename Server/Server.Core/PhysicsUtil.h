#pragma once

#include <irrlicht.h>
#include "Singleton.h"

class PhysicsUtil : public Singleton<PhysicsUtil>
{
	friend class Singleton<PhysicsUtil>;

public:
	PhysicsUtil();
	~PhysicsUtil()	= default;

	irr::IrrlichtDevice*		getDevice()			const;
	irr::scene::ISceneManager*	getSceneManager()	const;
	irr::video::IVideoDriver*	getVideoDriver()	const;


private:
	irr::IrrlichtDevice*		m_device;
	irr::scene::ISceneManager*	m_sceneManager;
	irr::video::IVideoDriver*	m_videoDriver;
};
