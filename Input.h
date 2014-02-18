#pragma once

class Input
{
	enum MOUSE_STATE { MOUSE_LEFT = 0, MOUSE_RIGHT = 1, MOUSE_SCROLL = 2 };
public:
	Input();
	~Input();

	bool Init();

	void Capture();
	// keyboard
	bool keyDown(DWORD key); // keyDown for a while
	bool keyUp(DWORD key);
	bool keyPress(DWORD key); // keyPressed just one time
	// mouse
	bool isButtonDown(int button); // mouseDown for a while
	bool isButtonPress(int button); // mousePressed just one time
	int getMouseMovingX();
	int getMouseMovingY();
	int getMouseMovingZ();
	long getMouseAbsX() { return m_ptAbsMousePos.x; }
	long getMouseAbsY() { return m_ptAbsMousePos.y; }
	bool CalcMousePosToWinRect(HWND hWnd);
	bool isMouseContain(int x, int y, int w, int h);

public:
	LPDIRECTINPUT8			m_dInput;
	LPDIRECTINPUTDEVICE8	m_keyboardDevice;
	BYTE					m_keyState[256]; // state of the keys
	BYTE					m_keyPressState[256]; // used for the keyPressed function

	LPDIRECTINPUTDEVICE8	m_mouseDevice;
	DIMOUSESTATE			m_CurrentmouseState, m_PreviousmouseState; // state of the keys(current, previous)
	POINT					m_ptAbsMousePos;
};
