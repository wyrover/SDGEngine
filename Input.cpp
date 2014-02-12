#include "Precompiled.h"

Input *INPUTS = nullptr;
Input::Input()
: m_pInput(0), m_pKey(0), m_pMou(0)
{
	INPUTS = this;
	assert(ENGINE != nullptr);
	memset(m_byCStk, 0, sizeof(BYTE)* 256);
	memset(m_byLStk, 0, sizeof(BYTE)* 256);
	memset(&m_CStm, 0, sizeof(DIMOUSESTATE));
	memset(&m_LStm, 0, sizeof(DIMOUSESTATE));

	//DirectInput 객체 생성.
	if (DirectInput8Create(ENGINE->instance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&m_pInput, NULL) != DI_OK)	return;

	//키보드 입력 디바이스 생성.
	if (m_pInput->CreateDevice(GUID_SysKeyboard, &m_pKey, NULL) != DI_OK) return;
	//키보드 디바이스의 협력 레벨을 설정한다.
	if (m_pKey->SetCooperativeLevel(ENGINE->Handle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE) != DI_OK) return; //DISCL_BACKGROUND
	//디바이스의 데이터 포맷 설정.
	if (m_pKey->SetDataFormat(&c_dfDIKeyboard) != DI_OK) return;
	//디바이스 접근 제어권 얻기.
	if (m_pKey->Acquire() != DI_OK) return;

	//마우스 입력 디바이스 생성.
	if (m_pInput->CreateDevice(GUID_SysMouse, &m_pMou, NULL) != DI_OK) return;
	//마우스 디바이스의 렵력 레벨 설정.
	if (m_pMou->SetCooperativeLevel(ENGINE->Handle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE) != DI_OK) return;
	//디바이스의 데이터 포맷 설정.
	if (m_pMou->SetDataFormat(&c_dfDIMouse) != DI_OK) return;
	//디바이스 접근 제어권 얻기.
	if (m_pMou->Acquire() != DI_OK) return;
}

Input::~Input()
{
	if (m_pKey)
	{
		m_pKey->Unacquire();
		SRELEASE(m_pKey);
	}
	if (m_pMou)
	{
		m_pMou->Unacquire();
		SRELEASE(m_pMou);
	}
	SRELEASE(m_pInput);
	INPUTS = nullptr;
}

void Input::Update()
{
	memcpy(m_byLStk, m_byCStk, sizeof(BYTE)* 256);
	if (m_pKey && m_pKey->GetDeviceState(256, (LPVOID)m_byCStk))
	{
		memset(m_byCStk, 0, sizeof(BYTE)* 256);
		m_pKey->Acquire();
	}
	memcpy(&m_LStm, &m_CStm, sizeof(DIMOUSESTATE));
	if (m_pMou && m_pMou->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_CStm))
	{
		memset(&m_CStm, 0, sizeof(DIMOUSESTATE));
		m_pMou->Acquire();
	}
}

bool Input::mouPos(HWND hWnd)
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

bool Input::MouseRectSection(int x, int y, int w, int h)
{
	//if (mouPos(g_pApp->GethWnd()))
	//{
	//	if (GetInput().m_ptAbsMousePos.x > x && GetInput().m_ptAbsMousePos.x < x + w &&
	//		GetInput().m_ptAbsMousePos.y > y && GetInput().m_ptAbsMousePos.y < y + h)
	//	{
	//		return true;
	//	}
	//}
	return false;
}