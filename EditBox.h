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
	char *buf; // 문자열 저장 배열
	bool isKorean; // 한글(true)/영문(false)
	int offset; // 캐럿의 위치
	int fontHeight; // 캐럿의 높이
	HWND m_hWnd;
	HDC hdc;
	PAINTSTRUCT ps;
	TEXTMETRIC tm;
};