#include <iostream>
#include <irrlicht.h>
#include <CEGUI\CEGUI.h>
#include <CEGUI\RendererModules\Irrlicht\Renderer.h>
#include <chrono>
#include "MainMenu.h"
#include "EventReceiver.h"
#include "LoadingWindows.h"
#include "WaitingRoom.h"
#include "InGameGUI.h"
#include "ConnectWindow.h"

#include "ClientCore.h"
#include "PlayerFactory.h"
#include "ProjectGlobals.h"
#include "CollectionComponent.h"
#include "Movement.h"
#include "MovementSystem.h"
#include "SpellSystem.h"
#include "WeaponSystem.h"
#include "Logger.h"

#include "NetworkModule.h"
#include "Logger.h"

#include "WeaponsConfiguration.h"
#include "SpellsConfiguration.h"

#define WIN_SIZE_X 1280
#define WIN_SIZE_Y 720

void initIrrlicht(irr::IrrlichtDevice*& device, irr::video::IVideoDriver*& driver, irr::scene::ISceneManager*& sceneManager, EventReceiver* receiver, irr::SKeyMap* keyMap)
{
	device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(WIN_SIZE_X, WIN_SIZE_Y),	32, false, false, false, receiver);
	driver = device->getVideoDriver();
	sceneManager = device->getSceneManager();
	irr::scene::IMeshSceneNode* cube = sceneManager->addCubeSceneNode(10.0f, 0,	-1, irr::core::vector3df(0.0f, 0.0f, 20.0f));
	cube->setMaterialFlag(irr::video::EMF_WIREFRAME, true);

	keyMap[0].Action = irr::EKA_MOVE_FORWARD;  // avancer
	keyMap[0].KeyCode = irr::KEY_KEY_Z;        // w
	keyMap[1].Action = irr::EKA_MOVE_BACKWARD; // reculer
	keyMap[1].KeyCode = irr::KEY_KEY_S;        // s
	keyMap[2].Action = irr::EKA_STRAFE_LEFT;   // a gauche
	keyMap[2].KeyCode = irr::KEY_KEY_Q;        // a
	keyMap[3].Action = irr::EKA_STRAFE_RIGHT;  // a droite
	keyMap[3].KeyCode = irr::KEY_KEY_D;        // d
	keyMap[4].Action = irr::EKA_JUMP_UP;       // saut
	keyMap[4].KeyCode = irr::KEY_SPACE;        // barre espace

	sceneManager->addCameraSceneNode(0, irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0), -1);
}

void initCEGUI(CEGUI::DefaultResourceProvider*& rp, CEGUI::XMLParser*& parser)
{
	rp = dynamic_cast<CEGUI::DefaultResourceProvider *>(CEGUI::System::getSingleton().getResourceProvider());
	if (rp == nullptr)
	{
		std::cout << "Problem during ressource provider instanciation process..." << std::endl;
		exit(0);
	}
	rp->setResourceGroupDirectory("schemes", "./datafiles/schemes/");
	rp->setResourceGroupDirectory("imagesets", "./datafiles/imagesets/");
	rp->setResourceGroupDirectory("fonts", "./datafiles/fonts/");
	rp->setResourceGroupDirectory("layouts", "./datafiles/layouts/");
	rp->setResourceGroupDirectory("looknfeels", "./datafiles/looknfeel/");
	rp->setResourceGroupDirectory("lua_scripts", "./datafiles/lua_scripts/");

	// set the default resource groups to be used
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
	// setup default group for validation schemas
	parser = CEGUI::System::getSingleton().getXMLParser();
	if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
		parser->setProperty("SchemaDefaultResourceGroup", "schemas");

	//Chargement des fichiers de police et de configuration de CEGUI
	CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-12.font");
	CEGUI::SchemeManager::getSingleton().createFromFile("WindowsLook.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("AlfiskoSkin.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("OgreTray.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("spells.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("Circles.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("Eclair.scheme");
}

void debugDisplayMousePos(irr::IrrlichtDevice* device)
{
	std::wstring text(L"Irrlicht - cursor position = X->");
	text += std::to_wstring(device->getCursorControl()->getPosition().X);
	text += std::wstring(L"    |    Y->");
	text += std::to_wstring(device->getCursorControl()->getPosition().Y);
	device->setWindowCaption(text.c_str());
}

void ceguiEventInjector(EventReceiver& receiver, irr::IrrlichtDevice* device)
{
	static bool lock;

	CEGUI::System& systemd = CEGUI::System::getSingleton();
	systemd.getDefaultGUIContext().injectMousePosition(device->getCursorControl()->getPosition().X, device->getCursorControl()->getPosition().Y);
	if (receiver.getMouseState().leftButtonDown == true)
		systemd.getDefaultGUIContext().injectMouseButtonDown(CEGUI::MouseButton::LeftButton);
	if (receiver.getMouseState().leftButtonDown == false)
		systemd.getDefaultGUIContext().injectMouseButtonUp(CEGUI::MouseButton::LeftButton);

	EventReceiver::keyStatesENUM *keyList = receiver.getKeyStateList();

	for (unsigned char i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
	{
		if (lock)
			break;
		if (keyList[i] == EventReceiver::keyStatesENUM::DOWN)
		{
			systemd.getDefaultGUIContext().injectKeyDown(static_cast<CEGUI::Key::Scan>(EventReceiver::irrlichtKeyToCEGUIKey((static_cast<irr::EKEY_CODE>(i)))));
			if ((static_cast<char>(i) >= 'a' && static_cast<char>(i) <= 'Z') || (static_cast<char>(i) >= 'A' && static_cast<char>(i) <= 'Z') || (static_cast<char>(i) >= '0' && static_cast<char>(i) <= '9') || (((keyList[irr::KEY_LSHIFT] == EventReceiver::keyStatesENUM::DOWN || keyList[irr::KEY_RSHIFT] == EventReceiver::keyStatesENUM::DOWN) && keyList[i] == EventReceiver::keyStatesENUM::DOWN && i == irr::KEY_PERIOD)))
			{
				if (((keyList[irr::KEY_LSHIFT] == EventReceiver::keyStatesENUM::DOWN || keyList[irr::KEY_RSHIFT] == EventReceiver::keyStatesENUM::DOWN) && keyList[i] == EventReceiver::keyStatesENUM::DOWN && i == irr::KEY_PERIOD))
				{
					systemd.getDefaultGUIContext().injectChar('.');
					continue;
				}
				else
					systemd.getDefaultGUIContext().injectChar(static_cast<char>(i));
			}
		}
		if (keyList[i] == EventReceiver::keyStatesENUM::UP)
			systemd.getDefaultGUIContext().injectKeyUp(static_cast<CEGUI::Key::Scan>(EventReceiver::irrlichtKeyToCEGUIKey(static_cast<irr::EKEY_CODE>(i))));
	}

	for (unsigned char i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
	{
		if (keyList[i] == EventReceiver::keyStatesENUM::DOWN && i != irr::KEY_LSHIFT && i != irr::KEY_RSHIFT && i != irr::KEY_BACK)
		{
			lock = true;
			break;
		}
		else if (keyList[i] == EventReceiver::keyStatesENUM::DOWN && i == irr::KEY_BACK)
			Sleep(70);
		else
			lock = false;
	}

}

int main(int argc, char* argv[])
{
	/*irr::SKeyMap keyMap[5];
	irr::IrrlichtDevice* device;
	irr::video::IVideoDriver* driver;
	irr::scene::ISceneManager* sceneManager;
	EventReceiver receiver;
	initIrrlicht(device, driver, sceneManager, &receiver, keyMap);

	//Hook Irrlicht renderer and Init and configure CEGUI
	CEGUI::IrrlichtRenderer& renderer = CEGUI::IrrlichtRenderer::create(*device);
	CEGUI::System& system = CEGUI::System::create(renderer);
	CEGUI::XMLParser* parser;
	CEGUI::DefaultResourceProvider* rp;
	initCEGUI(rp, parser);

	MainMenu menu(keyMap, sceneManager, device);
	menu.display();

	typedef std::chrono::duration<float, std::chrono::seconds::period> fpTime;
	std::chrono::high_resolution_clock::time_point last_time = std::chrono::high_resolution_clock::now();
	while (device->run())
	{
		if (device->isWindowActive()) //draw only if the window is active
		{
			auto begin = std::chrono::high_resolution_clock::now();
			float elapsed = fpTime(begin - last_time).count();
			CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(elapsed * 10);
			last_time = begin;
			driver->beginScene(true, true, irr::video::SColor(255, 150, 150, 150));
			sceneManager->drawAll(); //draw scene
			CEGUI::System::getSingleton().renderAllGUIContexts(); // draw gui
			debugDisplayMousePos(device); //Display mouse position on instead of windows title for debug purpose
			ceguiEventInjector(receiver, device);
			driver->endScene();
		}
	}
	device->drop();*/

	/*ClientCore	core;

	ecs::Entity	player = factory::PlayerFactory::createPlayer(1.0, 2.1, 0.0, 1, 1, 100);
	ecs::Entity predator = factory::PlayerFactory::createPredator(1.0, 4.2, 0.0, 2);
	ecs::Entity object = factory::ObjectFactory::createObject(2.0, 3.3, 0.0);

	core.addEntity(player);
	core.addEntity(predator);
	core.addEntity(object);

	core.dump();
	
	player[ecs::MOVEMENT] = new ecs::Movement(ecs::Position(2.0, 3.1, 0.0));

	ecs::MovementSystem::move(player);
	ecs::SpellSystem::launchSpell(predator, player);
	ecs::WeaponSystem::shootOnTarget(player, 5, true, predator);

	core.dump();
	getchar();
	*/

	/*
	Logger::getInstance().setup(ProjectGlobals::GAME_CLIENT_CORE_LOG_FILEPATH);
	ClientCore::getInstance().run();

	WeaponsConfiguration	weaponsConfig;
	SpellsConfiguration		spellsConfig;
	std::map<ecs::Weapon::WeaponType, ecs::Weapon>	weapons;
	std::map<ecs::Spell::SpellType, ecs::Spell>	spells;

	weaponsConfig.loadFromFile(WeaponsConfiguration::WEAPONS_FILENAME);
	spellsConfig.loadFromFile(SpellsConfiguration::SPELLS_FILENAME);

	spells = spellsConfig.getSpells();
	weapons = weaponsConfig.getWeapons();

	for (auto pair : spells)
	{
		pair.second.dump();
	}

	for (auto pair : weapons)
	{
		pair.second.dump();
	}
	getchar();
	*/

	Logger::getInstance().setup(ProjectGlobals::GAME_CLIENT_CORE_LOG_FILEPATH);
	ClientCore::getInstance().run();

	return (0);
}
