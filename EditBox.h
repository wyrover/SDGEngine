#pragma once

class EditBox
{
public:
	EditBox(){}
	EditBox(HWND hWnd);
	~EditBox();

	int GetCharWidth(HDC hdc, char *ch, int len);
	void SetCaret();
	inline int isDBCS(int nPos);
	int GetPrevOff(int nPos);
	int GetNextOff(int nPos);
	void Insert(int nPos, char *str);
	void Delete(int nPos, int nCount);
	LRESULT ImeProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

private:
	char *buf; // ���ڿ� ���� �迭
	bool isKorean; // �ѱ�(true)/����(false)
	int offset; // ĳ���� ��ġ
	int fontHeight; // ĳ���� ����
	HWND m_hWnd;
	HDC hdc;
	PAINTSTRUCT ps;
	TEXTMETRIC tm;
};