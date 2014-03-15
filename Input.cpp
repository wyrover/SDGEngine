#include "Precompiled.h"

namespace sidescroll
{
	Input::Input()
		: m_dInput(nullptr), m_keyboardDevice(nullptr), m_mouseDevice(nullptr)
	{
		ZeroMemory(m_keyState, sizeof(BYTE)* 256);
		ZeroMemory(m_keyPressState, sizeof(BYTE)* 256);
		ZeroMemory(&m_mouseState, sizeof(DIMOUSESTATE));
		ZeroMemory(&m_mousePressState, sizeof(DIMOUSESTATE));
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
		if (FAILED(DirectInput8Create(g_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&m_dInput, NULL)))
			return false;

		// Create a device for monitoring the keyboard
		if (FAILED(m_dInput->CreateDevice(GUID_SysKeyboard, &m_keyboardDevice, NULL)))
			return false;
		if (FAILED(m_keyboardDevice->SetCooperativeLevel(MySingleton<Engine>::GetSingleton()->Handle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))) //DISCL_BACKGROUND, DISCL_EXCLUSIVE
			return false;
		if (FAILED(m_keyboardDevice->SetDataFormat(&c_dfDIKeyboard)))
			return false;

		// Create a device for monitoring the mouse
		if (FAILED(m_dInput->CreateDevice(GUID_SysMouse, &m_mouseDevice, NULL)))
			return false;
		if (FAILED(m_mouseDevice->SetCooperativeLevel(MySingleton<Engine>::GetSingleton()->Handle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
			return false;
		if (FAILED(m_mouseDevice->SetDataFormat(&c_dfDIMouse)))
			return false;

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
		memcpy(&m_mousePressState, &m_mouseState, sizeof(DIMOUSESTATE));
		hr = m_mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
		if (hr)
		{
			memset(&m_mouseState, 0, sizeof(DIMOUSESTATE));
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
		return (m_mouseState.rgbButtons[button] & 0x80) ? true : false;
	}

	bool Input::isButtonPress(int button)
	{
		if ((m_mouseState.rgbButtons[button] & 0x80) && 
			(m_mouseState.rgbButtons[button] != m_mousePressState.rgbButtons[button]))
			return true;
		else
			return false;
	}

	int Input::getMouseMovingX()
	{
		return m_mouseState.lX;
	}

	int Input::getMouseMovingY()
	{
		return m_mouseState.lY;
	}

	int Input::getMouseMovingZ()
	{
		return m_mouseState.lZ;
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
		if (CalcMousePosToWinRect(MySingleton<Engine>::GetSingleton()->Handle()))
		{
			long absx = MySingleton<Input>::GetSingleton()->getMouseAbsX();
			long absy = MySingleton<Input>::GetSingleton()->getMouseAbsY();
			if (absx > x && absx < x + w && absy > y && absy < y + h)
			{
				return true;
			}
		}
		return false;
	}
}
