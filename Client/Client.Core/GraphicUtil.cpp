#include "GraphicUtil.h"
#include <irrlicht.h>
#include <CEGUI\CEGUI.h>
#include <CEGUI\RendererModules\Irrlicht\Renderer.h>
#include <Windows.h>

GraphicUtil::GraphicUtil()
{
	m_device = irr::createDevice(irr::video::EDT_DIRECT3D9, irr::core::dimension2d<irr::u32>(1280, 720), 16, false);
	if (!m_device)
	{
		// TODO: Throw exception
		std::cout << "Cannot create Device !" << std::endl;
	}

	m_driver = m_device->getVideoDriver();
	m_sceneManager = m_device->getSceneManager();
	m_keyMap = new irr::SKeyMap[5];
	m_keyMap[0].Action = irr::EKA_MOVE_FORWARD;  // avancer
	m_keyMap[0].KeyCode = irr::KEY_KEY_Z;        // w
	m_keyMap[1].Action = irr::EKA_MOVE_BACKWARD; // reculer
	m_keyMap[1].KeyCode = irr::KEY_KEY_S;        // s
	m_keyMap[2].Action = irr::EKA_STRAFE_LEFT;   // a gauche
	m_keyMap[2].KeyCode = irr::KEY_KEY_Q;        // a
	m_keyMap[3].Action = irr::EKA_STRAFE_RIGHT;  // a droite
	m_keyMap[3].KeyCode = irr::KEY_KEY_D;        // d
	m_keyMap[4].Action = irr::EKA_JUMP_UP;       // saut
	m_keyMap[4].KeyCode = irr::KEY_SPACE;        // barre espace
	initGraphics();
}

GraphicUtil::~GraphicUtil()
{
	if(m_FPSCamera)
		delete (m_FPSCamera);
	// Delete all?
}

void GraphicUtil::initGraphics()
{
	m_device->getCursorControl()->setVisible(false);
	m_sceneManager->getParameters()->setAttribute(irr::scene::OBJ_TEXTURE_PATH, "media/"); //TODO: Define Texture's Path
	m_device->setEventReceiver(&m_receiver);

	CEGUI::IrrlichtRenderer& renderer = CEGUI::IrrlichtRenderer::create(*m_device);
	CEGUI::System& system = CEGUI::System::create(renderer);
	CEGUI::XMLParser* parser;
	CEGUI::DefaultResourceProvider* rp;

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

	m_menu = new MainMenu(*this);
	m_menuPause = new MenuPause(*this);
	m_menuOptions = new MenuOptions(*this);
	this->setFPSCamera();
}

irr::IrrlichtDevice* GraphicUtil::getDevice()
{
	return m_device;
}

irr::scene::ISceneManager* GraphicUtil::getSceneManager()
{
	return m_sceneManager;
}

Camera* GraphicUtil::getFPSCamera()
{
	return (m_FPSCamera);
}

void GraphicUtil::CEGUIEventInjector()
{
	static bool lock;
	CEGUI::System& systemd = CEGUI::System::getSingleton();

	systemd.getDefaultGUIContext().injectMousePosition(m_device->getCursorControl()->getPosition().X, m_device->getCursorControl()->getPosition().Y);
	if (m_receiver.getMouseState().leftButtonDown == true)
		systemd.getDefaultGUIContext().injectMouseButtonDown(CEGUI::MouseButton::LeftButton);
	if (m_receiver.getMouseState().leftButtonDown == false)
		systemd.getDefaultGUIContext().injectMouseButtonUp(CEGUI::MouseButton::LeftButton);

	EventReceiver::keyStatesENUM *keyList = m_receiver.getKeyStateList();

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

EventReceiver& GraphicUtil::getCEGUIEventReceiver()
{
	return m_receiver;
}

MainMenu* GraphicUtil::getMainMenu()
{
	return m_menu;
}

MenuPause* GraphicUtil::getMenuPause()
{
	return m_menuPause;
}

MenuOptions* GraphicUtil::getMenuOptions()
{
	return m_menuOptions;
}

irr::video::IVideoDriver* GraphicUtil::getDriver()
{
	return m_driver;
}

void GraphicUtil::setGuiCamera()
{
	irr::core::vector3df position = m_sceneManager->getActiveCamera()->getPosition();
	irr::core::vector3df rotation = m_sceneManager->getActiveCamera()->getRotation();
	irr::core::vector3df target =  m_sceneManager->getActiveCamera()->getTarget();
	if (m_sceneManager->getActiveCamera())
		m_sceneManager->getActiveCamera()->remove();
	m_sceneManager->addCameraSceneNode(0, position, rotation, -1);
	m_sceneManager->getActiveCamera()->setTarget(target);
	m_device->getCursorControl()->setVisible(true);
}

void GraphicUtil::setFPSCamera()
{
	if (m_sceneManager->getActiveCamera())
		m_sceneManager->getActiveCamera()->remove();
	m_device->getCursorControl()->setVisible(false);
	m_FPSCamera = new Camera(ecs::Position(irr::core::vector3df(50.0f, 50.0f, -60.0f), irr::core::vector3df(-70.0f, 30.0f, -60.0f)), m_sceneManager);
	m_FPSCamera->init();
}