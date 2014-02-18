#include "Precompiled.h"

namespace sidescroll
{
	Input::Input()
		: m_dInput(nullptr), m_keyboardDevice(nullptr), m_mouseDevice(nullptr)
	{
		ZeroMemory(m_keyState, sizeof(BYTE)* 256);
		ZeroMemory(m_keyPressState, sizeof(BYTE)* 256);
		ZeroMemory(&m_CurrentmouseState, sizeof(DIMOUSESTATE));
		ZeroMemory(&m_PreviousmouseState, sizeof(DIMOUSESTATE));
	}

	Input::~Input()
	{
		if (m_keyboardDevice)
		{
			m_keyboardDevice->Unacquire();
			SRELEASE(m_keyboardDevice);
		}
		if (m_mouseDevice)
		{
			m_mouseDevice->Unacquire();
			SRELEASE(m_mouseDevice);
		}
		SRELEASE(m_dInput);
	}

	bool Input::Init()
	{
		// Create a direct input object
		if (FAILED(DirectInput8Create(ENGINE->instance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&m_dInput, NULL)))
			return false;

		// Create a device for monitoring the keyboard
		if (FAILED(m_dInput->CreateDevice(GUID_SysKeyboard, &m_keyboardDevice, NULL)))
			return false;
		if (FAILED(m_keyboardDevice->SetCooperativeLevel(ENGINE->Handle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))) //DISCL_BACKGROUND, DISCL_EXCLUSIVE
			return false;
		if (FAILED(m_keyboardDevice->SetDataFormat(&c_dfDIKeyboard)))
			return false;
		//if (FAILED(m_keyboardDevice->Acquire()))
		//	return false;

		// Create a device for monitoring the mouse
		if (FAILED(m_dInput->CreateDevice(GUID_SysMouse, &m_mouseDevice, NULL)))
			return false;
		if (FAILED(m_mouseDevice->SetCooperativeLevel(ENGINE->Handle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
			return false;
		if (FAILED(m_mouseDevice->SetDataFormat(&c_dfDIMouse)))
			return false;
		//if (FAILED(m_mouseDevice->Acquire()))
		//	return false;

		return true;
	}

	void Input::Capture()
	{
		HRESULT hr;

		// keyboard
		hr = m_keyboardDevice->GetDeviceState(sizeof(BYTE)* 256, (LPVOID)m_keyState);
		if (hr)
		{
			m_keyboardDevice->Acquire();
		}

		// mouse
		memcpy(&m_PreviousmouseState, &m_CurrentmouseState, sizeof(DIMOUSESTATE));
		hr = m_mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_CurrentmouseState);
		if (hr)
		{
			memset(&m_CurrentmouseState, 0, sizeof(DIMOUSESTATE));
			m_mouseDevice->Acquire();
		}
	}

	bool Input::keyDown(DWORD key)
	{
		return (m_keyState[key] & 0x80) ? true : false;
	}

	bool Input::keyUp(DWORD key)
	{
		return (m_keyState[key] & 0x80) ? false : true;
	}

	bool Input::keyPress(DWORD key)
	{
		//check for keydown
		if (keyDown(key)){
			m_keyPressState[key] = 1;
		}
		//check for key reaching the keydown state
		if (m_keyPressState[key] == 1){
			//check for key release
			if (keyUp(key))
				m_keyPressState[key] = 2;
		}

		//check if key has been pressed and released
		if (m_keyPressState[key] == 2){
			//reset the key status
			m_keyPressState[key] = 0;
			return true;
		}

		return false;
	}

	bool Input::isButtonDown(int button)
	{
		// 0 = left, 1 = right, 2 = middle
		return (m_CurrentmouseState.rgbButtons[button] & 0x80) ? true : false;
	}

	bool Input::isButtonPress(int button)
	{
		return ((m_CurrentmouseState.rgbButtons[button] & 0x80) && (m_CurrentmouseState.rgbButtons[button] != m_PreviousmouseState.rgbButtons[button])) ? true : false;
	}

	int Input::getMouseMovingX()
	{
		return m_CurrentmouseState.lX;
	}

	int Input::getMouseMovingY()
	{
		return m_CurrentmouseState.lY;
	}

	int Input::getMouseMovingZ()
	{
		return m_CurrentmouseState.lZ;
	}

	bool Input::CalcMousePosToWinRect(HWND hWnd)
	{
		RECT rtWinRect;

		if (::GetCursorPos(&m_ptAbsMousePos) == false)
			return false;

		GetWindowRect(hWnd, &rtWinRect);

		if (rtWinRect.left < m_ptAbsMousePos.x && rtWinRect.right >= m_ptAbsMousePos.x &&
			rtWinRect.top < m_ptAbsMousePos.y && rtWinRect.bottom >= m_ptAbsMousePos.y)
		{
			if (::ScreenToClient(hWnd, &m_ptAbsMousePos) == false) { return false; }
			return true;
		}
		else
		{
			m_ptAbsMousePos.x = 0; m_ptAbsMousePos.y = 0;
			return false;
		}

		return true;
	}

	bool Input::isMouseContain(int x, int y, int w, int h)
	{
		if (CalcMousePosToWinRect(ENGINE->Handle()))
		{
			long absx = ENGINE->INPUT()->getMouseAbsX();
			long absy = ENGINE->INPUT()->getMouseAbsY();
			if (absx > x && absx < x + w && absy > y && absy < y + h)
			{
				return true;
			}
		}
		return false;
	}
}
