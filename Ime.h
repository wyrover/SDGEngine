#pragma once

namespace SDGEngine
{
	class Ime
	{
	public:
		Ime(std::string font, int size);
		~Ime();

		int GetCharWidth(HDC hdc, char *ch, int len);
		void SetCaret();
		inline int isDBCS(int nPos);
		int GetPrevOff(int nPos);
		int GetNextOff(int nPos);
		void Insert(int nPos, char *str);
		void Delete(int nPos, int nCount);

		LRESULT wmChar(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
		LRESULT imeComposition(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
		LRESULT imeChar(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
		LRESULT wmSetFocus(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
		LRESULT wmKillFocus(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
		LRESULT wmKeyDown(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	private:
		char *buf; // ���ڿ� ���� �迭
		bool isKorean; // �ѱ�(true)/����(false)
		int offset; // ĳ���� ��ġ
		int fontHeight; // ĳ���� ����
		HIMC hImc; // context �ڵ�
		char tmpChar[3], *tmpComp;
		int length;
	};
}
