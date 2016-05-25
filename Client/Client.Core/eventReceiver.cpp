#include "EventReceiver.h"
#include "GraphicUtil.h"

EventReceiver::EventReceiver() :
	m_joystickState(), m_state(), m_keyState()
{
	for (EventReceiver::keyStatesENUM& e : m_keyState)
	{
		e = UP;
	}
}

bool EventReceiver::OnEvent(const irr::SEvent& event)
{
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		switch (event.MouseInput.Event)
		{
		case irr::EMIE_LMOUSE_PRESSED_DOWN:
			m_state.leftButtonDown = true;
			break;

		case irr::EMIE_LMOUSE_LEFT_UP:
			if (GraphicUtil::getInstance().isInFPSMode())
				m_events.push(EventReceiver::GameEventType::LEFT_ATTACK);
			else
				m_state.leftButtonDown = false;
			break;

		case irr::EMIE_MOUSE_MOVED:
			m_state.position.X = event.MouseInput.X;
			m_state.position.Y = event.MouseInput.Y;
			break;

		case irr::EMIE_MMOUSE_PRESSED_DOWN:
			m_events.push(EventReceiver::GameEventType::ZOOM);
			break;

		case irr::EMIE_MOUSE_WHEEL:
			if (event.MouseInput.Wheel < 0)
				m_events.push(EventReceiver::GameEventType::PREC_WEAPON);
			else
				m_events.push(EventReceiver::GameEventType::NEXT_WEAPON);
			break;

		default:
			// Mouse Wheel here (perhaps...)
			break;
		}
	}
	if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT&& event.JoystickEvent.Joystick == 0)
		m_joystickState = event.JoystickEvent;
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
	{
		if (GraphicUtil::getInstance().isInFPSMode())
		{
			switch (event.KeyInput.Key)
			{
			case irr::KEY_KEY_1:
				m_events.push(EventReceiver::GameEventType::CHANGE_MANAGER);
				break;

			case irr::KEY_KEY_2:
				m_events.push(EventReceiver::GameEventType::CHANGE_MANAGER);
				break;

			default:
				break;
			}
		}
		else
		{
			if (event.KeyInput.PressedDown == true)
			{
				m_keyState[event.KeyInput.Key] = DOWN;
			}
			else
			{
				m_keyState[event.KeyInput.Key] = UP;
			}
		}
	}
/*	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		switch (event.MouseInput.Event)
		{
		case irr::EMIE_LMOUSE_LEFT_UP:
			m_events.push(EventReceiver::GameEventType::LEFT_ATTACK);
			break;

		case irr::EMIE_MMOUSE_PRESSED_DOWN:
			m_events.push(EventReceiver::GameEventType::ZOOM);
			break;

		case irr::EMIE_MOUSE_WHEEL:
			if (event.MouseInput.Wheel < 0)
				m_events.push(EventReceiver::GameEventType::PREC_WEAPON);
			else
				m_events.push(EventReceiver::GameEventType::NEXT_WEAPON);
			break;

		default:
			break;
		}
	}
	else if (event.EventType == irr::EET_KEY_INPUT_EVENT)
	{
		switch (event.KeyInput.Key)
		{

		case irr::KEY_KEY_1:
			m_events.push(EventReceiver::GameEventType::CHANGE_MANAGER);
			break;

		case irr::KEY_KEY_2:
			m_events.push(EventReceiver::GameEventType::CHANGE_MANAGER);
			break;

		default:
			break;
		}
	}*/
	return false;
}

const irr::SEvent::SJoystickEvent& EventReceiver::getJoystickState() const
{
	return m_joystickState;
}

const EventReceiver::MouseState& EventReceiver::getMouseState() const
{
	return m_state;
}

EventReceiver::keyStatesENUM EventReceiver::getKeyState(irr::EKEY_CODE keyCode)
{
	return m_keyState[keyCode];
}

EventReceiver::keyStatesENUM* EventReceiver::getKeyStateList()
{
	return m_keyState;
}

unsigned char EventReceiver::irrlichtKeyToCEGUIKey(irr::EKEY_CODE kc)
{
	unsigned char irr2ceCODE[irr::KEY_KEY_CODES_COUNT];

	irr2ceCODE[irr::KEY_LBUTTON] = 0;  // Left mouse button
	irr2ceCODE[irr::KEY_RBUTTON] = 0;  // Right mouse button
	irr2ceCODE[irr::KEY_CANCEL] = 0;  // Control-break processing
	irr2ceCODE[irr::KEY_MBUTTON] = 0;  // Middle mouse button (three-button mouse)
	irr2ceCODE[irr::KEY_XBUTTON1] = 0;  // Windows 2000/XP: X1 mouse button
	irr2ceCODE[irr::KEY_XBUTTON2] = 0;  // Windows 2000/XP: X2 mouse button
	irr2ceCODE[irr::KEY_BACK] = CEGUI::Key::Backspace; //0x08;  // BACKSPACE key
	irr2ceCODE[irr::KEY_TAB] = CEGUI::Key::Key::Tab; //0x09;  // TAB key
	irr2ceCODE[irr::KEY_CLEAR] = 0;  // CLEAR key
	irr2ceCODE[irr::KEY_RETURN] = CEGUI::Key::Key::Return; //0x0D;  // ENTER key
	irr2ceCODE[irr::KEY_SHIFT] = CEGUI::Key::Key::LeftShift;  // SHIFT key
	irr2ceCODE[irr::KEY_CONTROL] = CEGUI::Key::Key::LeftControl;   // CTRL key
	irr2ceCODE[irr::KEY_MENU] = CEGUI::Key::Key::LeftAlt;  // ALT key
	irr2ceCODE[irr::KEY_PAUSE] = CEGUI::Key::Key::Pause;   // PAUSE key
	irr2ceCODE[irr::KEY_CAPITAL] = CEGUI::Key::Key::Capital;  // CAPS LOCK key
	irr2ceCODE[irr::KEY_KANA] = CEGUI::Key::Key::Kana;  // IME Kana mode
	irr2ceCODE[irr::KEY_JUNJA] = 0;  // IME Junja mode
	irr2ceCODE[irr::KEY_FINAL] = 0;  // IME final mode
	irr2ceCODE[irr::KEY_HANJA] = 0;  // IME Hanja mode
	irr2ceCODE[irr::KEY_KANJI] = 0;  // IME Kanji mode
	irr2ceCODE[irr::KEY_ESCAPE] = CEGUI::Key::Key::Escape;  // ESC key
	irr2ceCODE[irr::KEY_CONVERT] = CEGUI::Key::Key::Convert;  // IME convert
	irr2ceCODE[irr::KEY_NONCONVERT] = CEGUI::Key::Key::NoConvert;  // IME nonconvert
	irr2ceCODE[irr::KEY_ACCEPT] = 0;  // IME accept
	irr2ceCODE[irr::KEY_MODECHANGE] = 0;  // IME mode change request
	irr2ceCODE[irr::KEY_SPACE] = CEGUI::Key::Key::Space;  // SPACEBAR
	irr2ceCODE[irr::KEY_PRIOR] = CEGUI::Key::Key::PageUp;  // PAGE UP key
	irr2ceCODE[irr::KEY_NEXT] = CEGUI::Key::Key::PageDown;  // PAGE DOWN key
	irr2ceCODE[irr::KEY_END] = CEGUI::Key::Key::End;  // END key
	irr2ceCODE[irr::KEY_HOME] = CEGUI::Key::Key::Home;  // HOME key
	irr2ceCODE[irr::KEY_LEFT] = CEGUI::Key::Key::ArrowLeft;  // LEFT ARROW key
	irr2ceCODE[irr::KEY_UP] = CEGUI::Key::Key::ArrowUp;  // UP ARROW key
	irr2ceCODE[irr::KEY_RIGHT] = CEGUI::Key::Key::ArrowRight;  // RIGHT ARROW key
	irr2ceCODE[irr::KEY_DOWN] = CEGUI::Key::Key::ArrowDown;  // DOWN ARROW key
	irr2ceCODE[irr::KEY_SELECT] = 0;  // SELECT key
	irr2ceCODE[irr::KEY_PRINT] = CEGUI::Key::Key::SysRq;  // PRINT key
	irr2ceCODE[irr::KEY_EXECUT] = 0;  // EXECUTE key
	irr2ceCODE[irr::KEY_SNAPSHOT] = 0;  // PRINT SCREEN key
	irr2ceCODE[irr::KEY_INSERT] = CEGUI::Key::Key::Insert;//0x2D;  // INS key
	irr2ceCODE[irr::KEY_DELETE] = CEGUI::Key::Key::Delete;//0x2E;  // DEL key
	irr2ceCODE[irr::KEY_HELP] = 0;  // HELP key
	irr2ceCODE[irr::KEY_KEY_0] = CEGUI::Key::Key::Zero;   // 0 key
	irr2ceCODE[irr::KEY_KEY_1] = CEGUI::Key::Key::One;    // 1 key
	irr2ceCODE[irr::KEY_KEY_2] = CEGUI::Key::Key::Two;    // 2 key
	irr2ceCODE[irr::KEY_KEY_3] = CEGUI::Key::Key::Three;  // 3 key
	irr2ceCODE[irr::KEY_KEY_4] = CEGUI::Key::Key::Four;   // 4 key
	irr2ceCODE[irr::KEY_KEY_5] = CEGUI::Key::Key::Five;   // 5 key
	irr2ceCODE[irr::KEY_KEY_6] = CEGUI::Key::Key::Six;    // 6 key
	irr2ceCODE[irr::KEY_KEY_7] = CEGUI::Key::Key::Seven;  // 7 key
	irr2ceCODE[irr::KEY_KEY_8] = CEGUI::Key::Key::Eight;  // 8 key
	irr2ceCODE[irr::KEY_KEY_9] = CEGUI::Key::Key::Nine;   // 9 key
	irr2ceCODE[irr::KEY_KEY_A] = CEGUI::Key::Key::A;  // A key
	irr2ceCODE[irr::KEY_KEY_B] = CEGUI::Key::Key::B;  // B key
	irr2ceCODE[irr::KEY_KEY_C] = CEGUI::Key::Key::C;  // C key
	irr2ceCODE[irr::KEY_KEY_D] = CEGUI::Key::Key::D;  // D key
	irr2ceCODE[irr::KEY_KEY_E] = CEGUI::Key::Key::E;  // E key
	irr2ceCODE[irr::KEY_KEY_F] = CEGUI::Key::Key::F;  // F key
	irr2ceCODE[irr::KEY_KEY_G] = CEGUI::Key::Key::G;  // G key
	irr2ceCODE[irr::KEY_KEY_H] = CEGUI::Key::Key::H;  // H key
	irr2ceCODE[irr::KEY_KEY_I] = CEGUI::Key::Key::I;  // I key
	irr2ceCODE[irr::KEY_KEY_J] = CEGUI::Key::Key::J;  // J key
	irr2ceCODE[irr::KEY_KEY_K] = CEGUI::Key::Key::K;  // K key
	irr2ceCODE[irr::KEY_KEY_L] = CEGUI::Key::Key::L;  // L key
	irr2ceCODE[irr::KEY_KEY_M] = CEGUI::Key::Key::M;  // M key
	irr2ceCODE[irr::KEY_KEY_N] = CEGUI::Key::Key::N;  // N key
	irr2ceCODE[irr::KEY_KEY_O] = CEGUI::Key::Key::O;  // O key
	irr2ceCODE[irr::KEY_KEY_P] = CEGUI::Key::Key::P;  // P key
	irr2ceCODE[irr::KEY_KEY_Q] = CEGUI::Key::Key::Q;  // Q key
	irr2ceCODE[irr::KEY_KEY_R] = CEGUI::Key::Key::R;  // R key
	irr2ceCODE[irr::KEY_KEY_S] = CEGUI::Key::Key::S;  // S key
	irr2ceCODE[irr::KEY_KEY_T] = CEGUI::Key::Key::T;  // T key
	irr2ceCODE[irr::KEY_KEY_U] = CEGUI::Key::Key::U;  // U key
	irr2ceCODE[irr::KEY_KEY_V] = CEGUI::Key::Key::V;  // V key
	irr2ceCODE[irr::KEY_KEY_W] = CEGUI::Key::Key::W;  // W key
	irr2ceCODE[irr::KEY_KEY_X] = CEGUI::Key::Key::X;  // X key
	irr2ceCODE[irr::KEY_KEY_Y] = CEGUI::Key::Key::Y;  // Y key
	irr2ceCODE[irr::KEY_KEY_Z] = CEGUI::Key::Key::Z;  // Z key
	irr2ceCODE[irr::KEY_LWIN] = CEGUI::Key::Key::LeftWindows;  // Left Windows key (Microsoft� Natural� keyboard)
	irr2ceCODE[irr::KEY_RWIN] = CEGUI::Key::Key::RightWindows;  // Right Windows key (Natural keyboard)
	irr2ceCODE[irr::KEY_APPS] = CEGUI::Key::Key::AppMenu;  //Applications key (Natural keyboard)
	irr2ceCODE[irr::KEY_SLEEP] = CEGUI::Key::Key::Sleep;  // Computer Sleep key
	irr2ceCODE[irr::KEY_NUMPAD0] = CEGUI::Key::Key::Numpad0;  // Numeric keypad 0 key
	irr2ceCODE[irr::KEY_NUMPAD1] = CEGUI::Key::Key::Numpad1;  // Numeric keypad 1 key
	irr2ceCODE[irr::KEY_NUMPAD2] = CEGUI::Key::Key::Numpad2;  // Numeric keypad 2 key
	irr2ceCODE[irr::KEY_NUMPAD3] = CEGUI::Key::Key::Numpad3;  // Numeric keypad 3 key
	irr2ceCODE[irr::KEY_NUMPAD4] = CEGUI::Key::Key::Numpad4;  // Numeric keypad 4 key
	irr2ceCODE[irr::KEY_NUMPAD5] = CEGUI::Key::Key::Numpad5;  // Numeric keypad 5 key
	irr2ceCODE[irr::KEY_NUMPAD6] = CEGUI::Key::Key::Numpad6;  // Numeric keypad 6 key
	irr2ceCODE[irr::KEY_NUMPAD7] = CEGUI::Key::Key::Numpad7;  // Numeric keypad 7 key
	irr2ceCODE[irr::KEY_NUMPAD8] = CEGUI::Key::Key::Numpad8;  // Numeric keypad 8 key
	irr2ceCODE[irr::KEY_NUMPAD9] = CEGUI::Key::Key::Numpad9;  // Numeric keypad 9 key
	irr2ceCODE[irr::KEY_MULTIPLY] = CEGUI::Key::Key::Multiply;  // Multiply key
	irr2ceCODE[irr::KEY_ADD] = CEGUI::Key::Key::Add;  // Add key
	irr2ceCODE[irr::KEY_SEPARATOR] = 0;  // Separator key
	irr2ceCODE[irr::KEY_SUBTRACT] = CEGUI::Key::Key::Subtract;  // Subtract key
	irr2ceCODE[irr::KEY_DECIMAL] = CEGUI::Key::Key::Decimal;  // Decimal key
	irr2ceCODE[irr::KEY_DIVIDE] = CEGUI::Key::Key::Divide;  // Divide key
	irr2ceCODE[irr::KEY_F1] = CEGUI::Key::Key::F1;   // F1 key
	irr2ceCODE[irr::KEY_F2] = CEGUI::Key::Key::F2;   // F2 key
	irr2ceCODE[irr::KEY_F3] = CEGUI::Key::Key::F3;   // F3 key
	irr2ceCODE[irr::KEY_F4] = CEGUI::Key::Key::F4;   // F4 key
	irr2ceCODE[irr::KEY_F5] = CEGUI::Key::Key::F5;   // F5 key
	irr2ceCODE[irr::KEY_F6] = CEGUI::Key::Key::F6;   // F6 key
	irr2ceCODE[irr::KEY_F7] = CEGUI::Key::Key::F7;   // F7 key
	irr2ceCODE[irr::KEY_F8] = CEGUI::Key::Key::F8;   // F8 key
	irr2ceCODE[irr::KEY_F9] = CEGUI::Key::Key::F9;   // F9 key
	irr2ceCODE[irr::KEY_F10] = CEGUI::Key::Key::F10;  // F10 key
	irr2ceCODE[irr::KEY_F11] = CEGUI::Key::Key::F11;  // F11 key
	irr2ceCODE[irr::KEY_F12] = CEGUI::Key::Key::F12;  // F12 key
	irr2ceCODE[irr::KEY_F13] = CEGUI::Key::Key::F13;  // F13 key
	irr2ceCODE[irr::KEY_F14] = CEGUI::Key::Key::F14;  // F14 key
	irr2ceCODE[irr::KEY_F15] = CEGUI::Key::Key::F15;  // F15 key
	irr2ceCODE[irr::KEY_F16] = 0;  // F16 key
	irr2ceCODE[irr::KEY_F17] = 0;  // F17 key
	irr2ceCODE[irr::KEY_F18] = 0;  // F18 key
	irr2ceCODE[irr::KEY_F19] = 0;  // F19 key
	irr2ceCODE[irr::KEY_F20] = 0;  // F20 key
	irr2ceCODE[irr::KEY_F21] = 0;  // F21 key
	irr2ceCODE[irr::KEY_F22] = 0;  // F22 key
	irr2ceCODE[irr::KEY_F23] = 0;  // F23 key
	irr2ceCODE[irr::KEY_F24] = 0;  // F24 key
	irr2ceCODE[irr::KEY_NUMLOCK] = CEGUI::Key::Key::NumLock;  // NUM LOCK key
	irr2ceCODE[irr::KEY_SCROLL] = CEGUI::Key::Key::ScrollLock;  // SCROLL LOCK key
	irr2ceCODE[irr::KEY_LSHIFT] = CEGUI::Key::Key::LeftShift;  // Left SHIFT key
	irr2ceCODE[irr::KEY_RSHIFT] = CEGUI::Key::Key::RightShift;  // Right SHIFT key
	irr2ceCODE[irr::KEY_LCONTROL] = CEGUI::Key::Key::LeftControl;  // Left CONTROL key
	irr2ceCODE[irr::KEY_RCONTROL] = CEGUI::Key::Key::RightControl;  // Right CONTROL key
	irr2ceCODE[irr::KEY_LMENU] = CEGUI::Key::Key::LeftAlt;  // Left MENU key
	irr2ceCODE[irr::KEY_RMENU] = CEGUI::Key::Key::RightAlt;  // Right MENU key
	irr2ceCODE[irr::KEY_COMMA] = CEGUI::Key::Key::Comma;//0xBC;  // Comma Key  (;)
	irr2ceCODE[irr::KEY_PLUS] = CEGUI::Key::Key::Add;  // Plus Key   (+)
	irr2ceCODE[irr::KEY_MINUS] = CEGUI::Key::Key::Minus;  // Minus Key  (-)
	irr2ceCODE[irr::KEY_PERIOD] = CEGUI::Key::Key::Period;//0xBE;  // Period Key (.)
	irr2ceCODE[irr::KEY_ATTN] = 0;  // Attn key
	irr2ceCODE[irr::KEY_CRSEL] = 0;  // CrSel key
	irr2ceCODE[irr::KEY_EXSEL] = 0;  // ExSel key
	irr2ceCODE[irr::KEY_EREOF] = 0;  // Erase EOF key
	irr2ceCODE[irr::KEY_PLAY] = 0;  // Play key
	irr2ceCODE[irr::KEY_ZOOM] = 0;  // Zoom key
	irr2ceCODE[irr::KEY_PA1] = 0;  // PA1 key
	irr2ceCODE[irr::KEY_OEM_CLEAR] = 0;  // Clear key
	return irr2ceCODE[kc];
}

std::queue < EventReceiver::GameEventType > EventReceiver::getEvents() const
{
	return m_events;
}

EventReceiver::GameEventType EventReceiver::getEvent()
{
	GameEventType	event = m_events.front();

	m_events.pop();
	return event;
}
