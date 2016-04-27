#include <irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/System.h>
#include <CEGUI/RendererModules/Irrlicht/Renderer.h>
#include <windows.h>
#include <iostream>

#define WIN_SIZE_X 800
#define WIN_SIZE_Y 600

class MyEventReceiver : public irr::IEventReceiver
{
public:
	// We'll create a struct to record info on the mouse state
	struct SMouseState
	{
		irr::core::position2di Position;
		bool LeftButtonDown;
		SMouseState() : LeftButtonDown(false) { }
	} MouseState;

	// This is the one method that we have to implement
	virtual bool OnEvent(const irr::SEvent& event)
	{
		// Remember the mouse state
		if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{
			switch (event.MouseInput.Event)
			{
			case irr::EMIE_LMOUSE_PRESSED_DOWN:
				MouseState.LeftButtonDown = true;
				break;

			case irr::EMIE_LMOUSE_LEFT_UP:
				MouseState.LeftButtonDown = false;
				break;

			case irr::EMIE_MOUSE_MOVED:
				MouseState.Position.X = event.MouseInput.X;
				MouseState.Position.Y = event.MouseInput.Y;
				break;
			default:
				// We won't use the wheel
				break;
			}
		}

		// The state of each connected joystick is sent to us
		// once every run() of the Irrlicht device.  Store the
		// state of the first joystick, ignoring other joysticks.
		// This is currently only supported on Windows and Linux.
		if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
			&& event.JoystickEvent.Joystick == 0)
		{
			JoystickState = event.JoystickEvent;
		}

		return false;
	}

	const irr::SEvent::SJoystickEvent & GetJoystickState(void) const
	{
		return JoystickState;
	}

	const SMouseState & GetMouseState(void) const
	{
		return MouseState;
	}

	MyEventReceiver()
	{
	}

private:
	irr::SEvent::SJoystickEvent JoystickState;
};

class MenuActions
{
private:
	irr::SKeyMap *keyMap;
	irr::IrrlichtDevice *device;
	irr::video::IVideoDriver *driver;
	irr::scene::ISceneManager *sceneManager;
	CEGUI::System &systemd;
	irr::scene::ICameraSceneNode *&cam;
public:
	MenuActions(irr::SKeyMap *keyMap, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager, CEGUI::System &systemd, irr::scene::ICameraSceneNode *&cam)
			: keyMap(keyMap), device(device), driver(driver), sceneManager(sceneManager), systemd(systemd), cam(cam)
	{

	};
	~MenuActions() = default;
	bool jouer(const CEGUI::EventArgs& e)
	{
		std::cout << "Hiding CEGI GUI..." << std::endl;
		systemd.getDefaultGUIContext().setRootWindow(0);
		std::cout << "Unload current GUI..." << std::endl;
		std::cout << "Success ! Atl + F4 to quit for now ;)" << std::endl;
		sceneManager->getActiveCamera()->remove();
		cam = sceneManager->addCameraSceneNodeFPS(       // ajout de la camera FPS
			0,                                     // pas de noeud parent
			100.0f,                                // vitesse de rotation
			0.06f,                                  // vitesse de deplacement
			-1,                                    // pas de numero d'ID
			keyMap,                                // on change la keymap
			5);
		cam->setPosition(irr::core::vector3df(39.0f, 18.0f, 0.6f));
		cam->setRotation(irr::core::vector3df(17.0f, 270.0f, 0.0f));
		device->getCursorControl()->setVisible(false);
		return (true);
	};
	bool quit(const CEGUI::EventArgs& e)
	{
		std::cout << "Exiting..." << std::endl;
		exit(0);
	};
};

void initIrrlicht(irr::IrrlichtDevice *&device, irr::video::IVideoDriver *&driver, irr::scene::ISceneManager *&sceneManager, MyEventReceiver *receiver, irr::SKeyMap *&keyMap, irr::scene::ICameraSceneNode *&cam)
{
	device = irr::createDevice(  // creation du device
		irr::video::EDT_OPENGL,                       // API = OpenGL
		irr::core::dimension2d<irr::u32>(WIN_SIZE_X, WIN_SIZE_Y),    // taille fenetre 640x480p
		32, false, false, false, receiver);           // 32 bits par pixel

	driver =                // video driver
		device->getVideoDriver();
	sceneManager =         // scene manager
		device->getSceneManager();

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

	cam = sceneManager->addCameraSceneNode(       // ajout de la camera pour le GUI
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
	std::wstring text(L"DEBUG: X=");
	text += std::to_wstring(device->getCursorControl()->getPosition().X);
	text += std::wstring(L"  Y=");
	text += std::to_wstring(device->getCursorControl()->getPosition().Y);

	if (device->getSceneManager()->getActiveCamera() != nullptr)
	{
		text += std::wstring(L" CAM_X= ") + std::to_wstring(device->getSceneManager()->getActiveCamera()->getPosition().X);
		text += std::wstring(L" CAM_Y= ") + std::to_wstring(device->getSceneManager()->getActiveCamera()->getPosition().Y);
		text += std::wstring(L" CAM_Z= ") + std::to_wstring(device->getSceneManager()->getActiveCamera()->getPosition().Z);

		text += std::wstring(L" ROT_X= ") + std::to_wstring(device->getSceneManager()->getActiveCamera()->getRotation().X);
		text += std::wstring(L" ROT_Y= ") + std::to_wstring(device->getSceneManager()->getActiveCamera()->getRotation().Y);
		text += std::wstring(L" ROT_Z= ") + std::to_wstring(device->getSceneManager()->getActiveCamera()->getRotation().Z);
	}

	device->setWindowCaption(text.c_str());
}

void cegui_event_injector(CEGUI::System &systemd, MyEventReceiver &receiver, irr::IrrlichtDevice *device)
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
	irr::scene::ICameraSceneNode *cam;
	irr::SKeyMap *keyMap;
	irr::IrrlichtDevice* device;
	irr::video::IVideoDriver *driver;
	irr::scene::ISceneManager *sceneManager;
	MyEventReceiver receiver;
	initIrrlicht(device, driver, sceneManager, &receiver, keyMap, cam);

	//Hook Irrlicht renderer and Init and configure CEGUI
	CEGUI::IrrlichtRenderer &renderer = CEGUI::IrrlichtRenderer::create(*device);
	CEGUI::System &system = CEGUI::System::create(renderer);
	CEGUI::XMLParser *parser;
	CEGUI::DefaultResourceProvider* rp;
	initCEGUI(rp, parser);

	//Configuration du GUI
	CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-12.font");
	CEGUI::SchemeManager::getSingleton().createFromFile("WindowsLook.scheme");
	CEGUI::Window *windows = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("ButtonQuitter.layout");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(windows);
	CEGUI::System &systemd = CEGUI::System::getSingleton();

	//CEGUI Event handling and callbacks
	MenuActions test(keyMap, device, driver, sceneManager, systemd, cam);
	windows->getChild(0)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MenuActions::quit, &test));
	windows->getChild(2)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MenuActions::jouer, &test));

	irr::scene::IAnimatedMeshSceneNode *sydney = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("datafiles/ressources/sydney.md2"));
	sydney->setMD2Animation(irr::scene::EMAT_STAND);
	sydney->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	sydney->setMaterialFlag(irr::video::EMF_ANISOTROPIC_FILTER, false);
	sydney->setMaterialFlag(irr::video::EMF_ANTI_ALIASING, false);
	sydney->setMaterialTexture(0, driver->getTexture("datafiles/ressources/sydney.bmp"));

	while (device->run())
	{
		if (device->isWindowActive()) // draw only if the window is active
		{
			driver->beginScene(true, true, irr::video::SColor(255, 150, 255, 255));
			sceneManager->drawAll(); //draw scene
			systemd.renderAllGUIContexts(); // draw gui
			debug_display_mouse_pos(device); //Display mouse position on instead of windows title
			cegui_event_injector(systemd, receiver, device); //CEGUI event injector
			driver->endScene();
		}
	}
	device->drop();
	return 0;
}
