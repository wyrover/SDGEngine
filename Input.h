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

	//Ű���� ��� Ŭ��
	bool key(DWORD key) { return (m_byCStk[key] & 0x80) ? true : false; }
	//Ű���� �ѹ� Ŭ��
	bool KEY(DWORD key) { return ((m_byCStk[key] & 0x80) && (m_byCStk[key] != m_byLStk[key])) ? true : false; }
	//���콺 ��� Ŭ��
	bool mou(int mou) { return (m_CStm.rgbButtons[mou] & 0x80) ? true : false; }
	//���콺 ���� ��� Ŭ��
	bool moL() { return (m_CStm.rgbButtons[0] & 0x80) ? true : false; }
	//���콺 ������ ��� Ŭ��
	bool moR() { return (m_CStm.rgbButtons[1] & 0x80) ? true : false; }
	//���콺 �ѹ� Ŭ��
	bool MOU(int mou){ return ((m_CStm.rgbButtons[mou] & 0x80) && (m_CStm.rgbButtons[mou] != m_LStm.rgbButtons[mou])) ? true : false; }
	bool mouPos(HWND hWnd);
	bool MouseRectSection(int x, int y, int w, int h);

public:
	LPDIRECTINPUT8			m_pInput;
	LPDIRECTINPUTDEVICE8	m_pKey;
	BYTE					m_byCStk[256], m_byLStk[256];  //Ű���� ���°�(����,����)

	LPDIRECTINPUTDEVICE8	m_pMou;
	DIMOUSESTATE			m_CStm, m_LStm;			//���콺 ���°�(����,����)
	POINT					m_ptAbsMousePos;
};
