#include <iostream>
#include "mainMenu.h"
#include "eventReceiver.h"

#define WIN_SIZE_X 800
#define WIN_SIZE_Y 600

void initIrrlicht(irr::IrrlichtDevice *&device, irr::video::IVideoDriver *&driver, irr::scene::ISceneManager *&sceneManager, eventReceiver *receiver, irr::SKeyMap *&keyMap)
{
	device = irr::createDevice(  // creation du device
		irr::video::EDT_DIRECT3D9,                       // API = OpenGL
		irr::core::dimension2d<irr::u32>(WIN_SIZE_X, WIN_SIZE_Y),    // taille fenetre 640x480p
		32, false, false, false, receiver);           // 32 bits par pixel

	driver =                // video driver
		device->getVideoDriver();
	sceneManager =         // scene manager
		device->getSceneManager();

	irr::scene::IMeshSceneNode* cube =         // pointeur vers le node
		sceneManager->addCubeSceneNode(        // la creation du cube
			10.0f,                             // cote de 10 unites
			0,                                 // parent = racine
			-1,                                // pas d'ID
			irr::core::vector3df(              // le vecteur de position
				0.0f,                          // origine en X
				0.0f,                          // origine en Y
				20.0f));                       // +20 unites en Z

	cube->setMaterialFlag(irr::video::EMF_WIREFRAME, true);


	keyMap = new irr::SKeyMap[5];                    // re-assigne les commandes
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

											   //Mode gui

	sceneManager->addCameraSceneNode(       // ajout de la camera FPS
		0,                                     // pas de noeud parent
		irr::core::vector3df(0, 0, 0),
		irr::core::vector3df(0, 0, 0),
		-1);
}

void initCEGUI(CEGUI::DefaultResourceProvider *&rp, CEGUI::XMLParser *&parser)
{
	rp = static_cast<CEGUI::DefaultResourceProvider*>
		(CEGUI::System::getSingleton().getResourceProvider());
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
}

void debug_display_mouse_pos(irr::IrrlichtDevice *device)
{
	std::wstring text(L"Irrlicht - cursor position = X->");
	text += std::to_wstring(device->getCursorControl()->getPosition().X);
	text += std::wstring(L"    |    Y->");
	text += std::to_wstring(device->getCursorControl()->getPosition().Y);
	device->setWindowCaption(text.c_str());
}

void cegui_event_injector(CEGUI::System &systemd, eventReceiver &receiver, irr::IrrlichtDevice *device)
{
	systemd.getDefaultGUIContext().injectMousePosition(device->getCursorControl()->getPosition().X, device->getCursorControl()->getPosition().Y);
	systemd.getDefaultGUIContext().injectMouseButtonClick(CEGUI::MouseButton::LeftButton);
	if (receiver.GetMouseState().LeftButtonDown == true)
		systemd.getDefaultGUIContext().injectMouseButtonDown(CEGUI::MouseButton::LeftButton);
	if (receiver.GetMouseState().LeftButtonDown == false)
		systemd.getDefaultGUIContext().injectMouseButtonUp(CEGUI::MouseButton::LeftButton);
}

int main(void) {
	//Init Irrlicht Engine
	irr::SKeyMap *keyMap;
	irr::IrrlichtDevice* device;
	irr::video::IVideoDriver *driver;
	irr::scene::ISceneManager *sceneManager;
	eventReceiver receiver;
	initIrrlicht(device, driver, sceneManager, &receiver, keyMap);

	//Hook Irrlicht renderer and Init and configure CEGUI
	CEGUI::IrrlichtRenderer &renderer = CEGUI::IrrlichtRenderer::create(*device);
	CEGUI::System &system = CEGUI::System::create(renderer);
	CEGUI::XMLParser *parser;
	CEGUI::DefaultResourceProvider* rp;
	initCEGUI(rp, parser);

	//Chargement des fichiers de police et de configuration de CEGUI
	CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-12.font");
	CEGUI::SchemeManager::getSingleton().createFromFile("WindowsLook.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("AlfiskoSkin.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("OgreTray.scheme");

	mainMenu menu(keyMap, sceneManager, device);
	menu.display();
	while (device->run())
	{
		if (device->isWindowActive()) //draw only if the window is active
		{
			driver->beginScene(true, true, irr::video::SColor(255, 150, 255, 255));
			sceneManager->drawAll(); //draw scene
			CEGUI::System::getSingleton().renderAllGUIContexts(); // draw gui
			debug_display_mouse_pos(device); //Display mouse position on instead of windows title for debug purpose
			cegui_event_injector(CEGUI::System::getSingleton(), receiver, device);
			driver->endScene();
		}
	}
	device->drop();
	return (0);
}
