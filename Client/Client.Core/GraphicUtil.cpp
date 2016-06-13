#include <thread>
#include <chrono>

#include "GraphicUtil.h"
#include "ClientCore.h"
#include "SceneMesh.h"
#include "ProjectGlobals.h"
#include "WeaponManagerSystem.h"
#include "ressource.h"
#include "NodePickable.h"
#include "Team.h"

#include <irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Irrlicht/Renderer.h>

#ifdef _WIN32
  #include <Windows.h>
#endif

GraphicUtil::GraphicUtil() :
	m_device(nullptr), m_sceneManager(nullptr), m_driver(nullptr), m_FPSCamera(nullptr), m_guiCamera(nullptr), m_receiver(), m_keyMap(nullptr), m_menu(nullptr), m_menuPause(nullptr), m_menuOptions(nullptr), m_connectWindow(nullptr), m_salon(nullptr), m_hud(nullptr), m_isInFPSMode(false), m_skyBox(nullptr)
{
	irr::video::E_DRIVER_TYPE driver;

#ifdef _WIN32
	driver = irr::video::EDT_DIRECT3D9;
#else
	driver = irr::video::EDT_OPENGL;
#endif

	m_device = irr::createDevice(driver, irr::core::dimension2d<irr::u32>(1280, 720), 16, false);
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
}

void GraphicUtil::initGraphics()
{
	//Cursor
	m_device->getCursorControl()->setVisible(false);

	//Texture obj path
	m_sceneManager->getParameters()->setAttribute(irr::scene::OBJ_TEXTURE_PATH, "media/");

	//Event Reveiver
	m_device->setEventReceiver(&m_receiver);

	//Target


	//Gui
	CEGUI::IrrlichtRenderer& renderer = CEGUI::IrrlichtRenderer::create(*m_device);
	CEGUI::System& system = CEGUI::System::create(renderer);
	CEGUI::XMLParser* parser;
	CEGUI::DefaultResourceProvider* rp;

	rp = dynamic_cast<CEGUI::DefaultResourceProvider *>(CEGUI::System::getSingleton().getResourceProvider());
	if (rp == nullptr)
	{
		LOG_ERROR(GENERAL) << "Problem during ressource provider instanciation process...";
		exit(1);
	}

	rp->setResourceGroupDirectory("schemes", "./datafiles/schemes/");
	rp->setResourceGroupDirectory("imagesets", "./datafiles/imagesets/");
	rp->setResourceGroupDirectory("fonts", "./datafiles/fonts/");
	rp->setResourceGroupDirectory("layouts", "./datafiles/layouts/");
	rp->setResourceGroupDirectory("looknfeels", "./datafiles/looknfeel/");
	rp->setResourceGroupDirectory("lua_scripts", "./datafiles/lua_scripts/");

	CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
	
	parser = CEGUI::System::getSingleton().getXMLParser();
	if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
		parser->setProperty("SchemaDefaultResourceGroup", "schemas");

	CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-12.font");
	CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-14-NoScale.font");
	CEGUI::FontManager::getSingleton().createFromFile("Jura-10.font");
	CEGUI::SchemeManager::getSingleton().createFromFile("WindowsLook.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("AlfiskoSkin.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("OgreTray.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("spells.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("Circles.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("Eclair.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("MainMenu.scheme");

	m_menu = new MainMenu(*this);
	m_menuPause = new MenuPause(*this);
	m_menuOptions = new MenuOptions(*this);
	m_connectWindow = new ConnectWindow(*this);
	m_salon = new WaitingRoom(*this);
	m_hud = new InGameGUI();
	m_masterList = new MasterList(*this);
	m_blindFx = new Blind();
	m_touchedFx = new TouchedFx();
	m_deadGUI = new YourDead();
	m_scoreTab = new scoreTab(*this);

	if (!ProjectGlobals::getNoMenu())
	{
		this->setFPSCamera();
		this->setGuiCamera();
	}

#ifdef _WIN32
	HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);
	HICON hSmallIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(ID_ICON), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	irr::video::SExposedVideoData exposedData = m_driver->getExposedVideoData();
	HWND hWnd = reinterpret_cast<HWND>(exposedData.D3D9.HWnd);
	SendMessage(hWnd, WM_SETICON, ICON_SMALL, (long)hSmallIcon);
#endif
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
		  std::this_thread::sleep_for(std::chrono::milliseconds(70));
		else
			lock = false;
	}
}

EventReceiver& GraphicUtil::getCEGUIEventReceiver()
{
	return m_receiver;
}

ConnectWindow* GraphicUtil::getConnectWindow()
{
	return m_connectWindow;
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

MasterList* GraphicUtil::getMasterList()
{
	return m_masterList;
}

bool GraphicUtil::isInFPSMode() const
{
	return m_isInFPSMode;
}

void GraphicUtil::initSky()
{
	m_driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
	m_driver->setTextureCreationFlag(irr::video::ETCF_ALWAYS_32_BIT, true);

	m_skyBox = m_sceneManager->addSkyBoxSceneNode(
		m_driver->getTexture("Media/irrlicht2_up.jpg"),
		m_driver->getTexture("Media/irrlicht2_dn.jpg"),
		m_driver->getTexture("Media/irrlicht2_lf.jpg"),
		m_driver->getTexture("Media/irrlicht2_rt.jpg"),
		m_driver->getTexture("Media/irrlicht2_ft.jpg"),
		m_driver->getTexture("Media/irrlicht2_bk.jpg"));
	m_skyBox->setID(nodePickable::NOT_PICKABLE);

	m_driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);
}

InGameGUI* GraphicUtil::getHUD()
{
	return m_hud;
}

YourDead* GraphicUtil::getDeadGUI()
{
	return m_deadGUI;
}

TouchedFx* GraphicUtil::getTouchedFx()
{
	return m_touchedFx;
}

WaitingRoom* GraphicUtil::getWaitingRoom()
{
	return (m_salon);
}

irr::video::IVideoDriver* GraphicUtil::getDriver()
{
	return m_driver;
}

Blind* GraphicUtil::getBlindFx()
{
	return m_blindFx;
}

scoreTab* GraphicUtil::getScoreTab()
{
	return m_scoreTab;
}

void GraphicUtil::setGuiCamera()
{
	m_isInFPSMode = false;
	irr::core::vector3df position = m_sceneManager->getActiveCamera()->getPosition();
	irr::core::vector3df rotation = m_sceneManager->getActiveCamera()->getRotation();
	irr::core::vector3df target =  m_sceneManager->getActiveCamera()->getTarget();
	if (m_sceneManager->getActiveCamera())
	{
		m_sceneManager->getActiveCamera()->removeAnimators();
		m_sceneManager->getActiveCamera()->remove();
	}
	m_sceneManager->addCameraSceneNode(0, position, rotation, -1);
	m_sceneManager->getActiveCamera()->setTarget(target);
	m_device->getCursorControl()->setVisible(true);
}

void GraphicUtil::setFPSCamera()
{
	ecs::Entity*	localPlayer = PlayerManager::getInstance().getCurrentPlayer();
	ecs::Team*		team = nullptr;
	auto&			players = PlayerManager::getInstance().getEntities();

	std::srand(std::time(nullptr));

	ecs::Position	cameraPosition(
		irr::core::vector3df(50.F + (std::rand() % 100) + 20, 50.F, -60.F),
		irr::core::vector3df(0.F, 0.F, 0.F));

	if (m_sceneManager->getActiveCamera())
	{
		cameraPosition.setVectorPosition(m_sceneManager->getActiveCamera()->getAbsolutePosition());
		cameraPosition.setVectorRotation(m_sceneManager->getActiveCamera()->getTarget());
		m_sceneManager->getActiveCamera()->remove();
	}
	
	if (localPlayer)
	{
		team = dynamic_cast<ecs::Team*>((*localPlayer)[ecs::AComponent::ComponentType::TEAM]);

		switch (team->getTeam())
		{
			case ecs::Team::TeamType::Predator:
				cameraPosition.setVectorPosition(irr::core::vector3df(147.5F, 112.F, 833.F));
				break;
			case ecs::Team::TeamType::Team1:
				cameraPosition.setVectorRotation(irr::core::vector3df(-45.F, 0.F, 0.F));
				cameraPosition.setVectorPosition(irr::core::vector3df(190.F + localPlayer->getOwner() * 30, 304.F, -62.F));
				break;
			case ecs::Team::TeamType::Team2:
				cameraPosition.setVectorRotation(irr::core::vector3df(45.F, 0.F, 0.F));
				cameraPosition.setVectorPosition(irr::core::vector3df(-65.F - localPlayer->getOwner() * 30, 304.F, -62.F));
				break;
			default:
				break;
		}
	}
	m_device->getCursorControl()->setVisible(false);
	PlayerManager::getInstance().removeWeaponScene();

	m_FPSCamera = new Camera(cameraPosition, m_sceneManager);

	ClientCore&		clientCore = ClientCore::getInstance();
	ecs::Entity*	map;

	//Collisions
	if ((map = clientCore.getMap()) != nullptr)
	{
		dynamic_cast<ecs::SceneMesh*>((*map)[ecs::AComponent::ComponentType::SCENE])->setCollision(true);
	}

	for (auto it = players.begin(); it != players.end(); ++it)
	{
		if (it->second != localPlayer)
		{
			ecs::SceneAnimatedMesh* scene = dynamic_cast<ecs::SceneAnimatedMesh*>((*it->second)[ecs::AComponent::ComponentType::SCENE]);
			if (scene != nullptr)
			{
				scene->setCollision(false);
			}
		}
	}

	m_isInFPSMode = true;
	PlayerManager::getInstance().initPlayersWeapons();
}
