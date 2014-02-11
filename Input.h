#pragma once

class Input;
extern Input *INPUTS;
class Input
{
public:
	Input();
	~Input();

	void Init();
	void Update();

	//키보드 계속 클릭
	bool key(DWORD key) { return (m_byCStk[key] & 0x80) ? true : false; }
	//키보드 한번 클릭
	bool KEY(DWORD key) { return ((m_byCStk[key] & 0x80) && (m_byCStk[key] != m_byLStk[key])) ? true : false; }
	//마우스 계속 클릭
	bool mou(int mou) { return (m_CStm.rgbButtons[mou] & 0x80) ? true : false; }
	//마우스 왼쪽 계속 클릭
	bool moL() { return (m_CStm.rgbButtons[0] & 0x80) ? true : false; }
	//마우스 오른쪽 계속 클릭
	bool moR() { return (m_CStm.rgbButtons[1] & 0x80) ? true : false; }
	//마우스 한번 클릭
	bool MOU(int mou){ return ((m_CStm.rgbButtons[mou] & 0x80) && (m_CStm.rgbButtons[mou] != m_LStm.rgbButtons[mou])) ? true : false; }
	bool mouPos(HWND hWnd);
	bool MouseRectSection(int x, int y, int w, int h);

public:
	LPDIRECTINPUT8			m_pInput;
	LPDIRECTINPUTDEVICE8	m_pKey;
	BYTE					m_byCStk[256], m_byLStk[256];  //키보드 상태값(현재,이전)

	LPDIRECTINPUTDEVICE8	m_pMou;
	DIMOUSESTATE			m_CStm, m_LStm;			//마우스 상태값(현재,이전)
	POINT					m_ptAbsMousePos;
};
