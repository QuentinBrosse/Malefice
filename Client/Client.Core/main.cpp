#include <iostream>
#include <irrlicht.h>
#include <CEGUI\CEGUI.h>
#include <CEGUI\RendererModules\Irrlicht\Renderer.h>
#include "MainMenu.h"
#include "EventReceiver.h"
#include "LoadingWindows.h"
#include "WaitingRoom.h"
#include "InGameGUI.h"

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
#include "main.h"

#include "WeaponsConfiguration.h"
#include "SpellsConfiguration.h"

#define WIN_SIZE_X 1280
#define WIN_SIZE_Y 720

#define _CLIENT // Required for shared libraries

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
	CEGUI::System& systemd = CEGUI::System::getSingleton();
	systemd.getDefaultGUIContext().injectMousePosition(device->getCursorControl()->getPosition().X, device->getCursorControl()->getPosition().Y);
	systemd.getDefaultGUIContext().injectMouseButtonClick(CEGUI::MouseButton::LeftButton);
	if (receiver.getMouseState().leftButtonDown == true)
		systemd.getDefaultGUIContext().injectMouseButtonDown(CEGUI::MouseButton::LeftButton);
	if (receiver.getMouseState().leftButtonDown == false)
		systemd.getDefaultGUIContext().injectMouseButtonUp(CEGUI::MouseButton::LeftButton);
}

int main(int argc, char* argv[])
{
/*	irr::SKeyMap keyMap[5];
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

	InGameGUI gameGUI;
	gameGUI.display();
	gameGUI.setHealthPoint(90);
	gameGUI.setEnergyPoint(42);
	gameGUI.timerStart();
	gameGUI.enablePower(3);
	gameGUI.setTeam1Score(42);
	gameGUI.setTeam2Score(0);
	while (device->run())
	{
		if (device->isWindowActive()) //draw only if the window is active
		{
			gameGUI.refreshTime();

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
	return (0);
}
