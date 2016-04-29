#include <iostream>

#include "mainMenu.h"
#include "eventReceiver.h"

#define WIN_SIZE_X 800
#define WIN_SIZE_Y 600

void initIrrlicht(irr::IrrlichtDevice *&device, irr::video::IVideoDriver *&driver, irr::scene::ISceneManager *&sceneManager, eventReceiver *receiver, irr::SKeyMap *keyMap)
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

void initCEGUI(CEGUI::DefaultResourceProvider *&rp, CEGUI::XMLParser *&parser)
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
}

void debugDisplayMousePos(irr::IrrlichtDevice *device)
{
	std::wstring text(L"Irrlicht - cursor position = X->");
	text += std::to_wstring(device->getCursorControl()->getPosition().X);
	text += std::wstring(L"    |    Y->");
	text += std::to_wstring(device->getCursorControl()->getPosition().Y);
	device->setWindowCaption(text.c_str());
}

void ceguiEventInjector(CEGUI::System &systemd, eventReceiver &receiver, irr::IrrlichtDevice *device)
{
	systemd.getDefaultGUIContext().injectMousePosition(device->getCursorControl()->getPosition().X, device->getCursorControl()->getPosition().Y);
	systemd.getDefaultGUIContext().injectMouseButtonClick(CEGUI::MouseButton::LeftButton);
	if (receiver.getMouseState().leftButtonDown == true)
		systemd.getDefaultGUIContext().injectMouseButtonDown(CEGUI::MouseButton::LeftButton);
	if (receiver.getMouseState().leftButtonDown == false)
		systemd.getDefaultGUIContext().injectMouseButtonUp(CEGUI::MouseButton::LeftButton);
}

int main(void) {
	//Init Irrlicht Engine
	irr::SKeyMap keyMap[5];
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
			driver->beginScene(true, true, irr::video::SColor(255, 255, 255, 255));
			sceneManager->drawAll(); //draw scene
			CEGUI::System::getSingleton().renderAllGUIContexts(); // draw gui
			debugDisplayMousePos(device); //Display mouse position on instead of windows title for debug purpose
			ceguiEventInjector(CEGUI::System::getSingleton(), receiver, device);
			driver->endScene();
		}
	}
	device->drop();
	return (0);
}
