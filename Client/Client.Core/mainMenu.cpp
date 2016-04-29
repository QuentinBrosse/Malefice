#include "MainMenu.h"

MainMenu::MainMenu(irr::SKeyMap* keyMap, irr::scene::ISceneManager* sceneManager, irr::IrrlichtDevice* device) : m_systemd(CEGUI::System::getSingleton()), m_keyMap(keyMap), m_sceneManager(sceneManager), m_device(device)
{
	m_windows = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("mainMenu.layout");
	m_windows->getChild(0)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenu::onQuitButtonClicked, this));
	m_windows->getChild(2)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenu::onPlayButtonClicked, this));

}

void MainMenu::display()
{
	m_systemd.getDefaultGUIContext().setRootWindow(m_windows);
}

void MainMenu::hide()
{
	m_systemd.getDefaultGUIContext().setRootWindow(0);
}

bool MainMenu::onPlayButtonClicked(const CEGUI::EventArgs& e)
{
	std::cout << "Hiding CEGI GUI..." << std::endl;
	m_systemd.getDefaultGUIContext().setRootWindow(0);
	std::cout << "Unload current GUI..." << std::endl;
	std::cout << "Loading camera and keymaping..." << std::endl;

	m_sceneManager->getActiveCamera()->remove();
	m_sceneManager->addCameraSceneNodeFPS(       // ajout de la camera FPS
		0,                                     // pas de noeud parent
		100.0f,                                // vitesse de rotation
		0.06f,                                  // vitesse de deplacement
		-1,                                    // pas de numero d'ID
		m_keyMap,                                // on change la keymap
		5);
	m_device->getCursorControl()->setVisible(false);
	return (true);
}

bool MainMenu::onOptionButtonClicked(const CEGUI::EventArgs& e)
{
	return (false);
}

bool MainMenu::onQuitButtonClicked(const CEGUI::EventArgs& e)
{
	std::cout << "Exiting..." << std::endl;
	exit(0);
	return (false);
}