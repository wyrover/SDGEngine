#include "Precompiled.h"

namespace sidescroll
{
	Ime::Ime(std::string font, int size)
	{
		isKorean = false;
		buf = (char *)malloc(256);
		memset(buf, 0, 256);
		offset = 0;
	}

	Ime::~Ime()
	{
		free(buf);
	}

	int Ime::GetCharWidth(HDC hdc, char *ch, int len)
	{
		//SIZE sz;
		//GetTextExtentPoint32(hdc, ch, len, &sz);
		//return sz.cx;
		return 0;
	}

	void Ime::SetCaret()
	{
		//SIZE sz;
		//HDC hdc;
		//int toff;
		//int caretwidth;

		//hdc = GetDC(m_hWnd);
		//if (isKorean)
		//{
		//	toff = offset - 2;
		//	caretwidth = GetCharWidth(hdc, buf + toff, 2);
		//}
		//else
		//{
		//	toff = offset;
		//	caretwidth = 2;
		//}
		//CreateCaret(m_hWnd, NULL, caretwidth, fontHeight);
		//ShowCaret(m_hWnd);

		//GetTextExtentPoint32(hdc, buf, toff, &sz);
		//SetCaretPos(sz.cx, 0);
		//ReleaseDC(m_hWnd, hdc);
	}

	inline int Ime::isDBCS(int nPos)
	{
		return (IsDBCSLeadByte(buf[nPos]));
	}

	int Ime::GetPrevOff(int nPos)
	{
		int n, size;

		if (nPos == 0)
			return 0;

		for (n = 0;;)
		{
			if (isDBCS(n))
				size = 2;
			else
				size = 1;
			n += size;
			if (n >= nPos) break;
		}
		return n - size;
	}

	int Ime::GetNextOff(int nPos)
	{
		if (isDBCS(nPos))
			return nPos + 2;
		else
			return nPos + 1;
	}

	void Ime::Insert(int nPos, char *str)
	{
		int len;
		int movelen;

		len = strlen(str);
		if (len == 0) return;
		movelen = strlen(buf + nPos) + 1;
		memmove(buf + nPos + len, buf + nPos, movelen);
		memcpy(buf + nPos, str, len);
	}

	void Ime::Delete(int nPos, int nCount)
	{
		int movelen;

		if (nCount == 0) return;
		if ((int)strlen(buf) < nPos + nCount) return;

		movelen = strlen(buf + nPos + nCount) + 1;
		memmove(buf + nPos, buf + nPos + nCount, movelen);
	}

	LRESULT Ime::wmChar(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
	{
		switch (iMessage)
		{
		case WM_CHAR:
			// 영어, 숫자일때 오는 메세지, wParam은 오직 1byte이다.
			// LOWORD(lParam) means 입력받은 횟수
			if (wParam == 8) // backspace 일때 문자 입력안되게
				return 0;
			tmpChar[0] = (char)wParam; tmpChar[1] = NULL;
			for (int i = 0; i < LOWORD(lParam); i++)
			{
				Insert(offset, tmpChar);
				offset += strlen(tmpChar);
			}
			isKorean = false; // because WM_CHAR means english or numeric.
			InvalidateRect(hWnd, NULL, true); // make wm_paint message
			SetCaret();
			return 0;
		}

		return 0;
	}

	LRESULT Ime::imeComposition(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
	{
		switch (iMessage)
		{
		case WM_IME_COMPOSITION:
			// if character composition is going
			if (lParam & GCS_COMPSTR)
			{
				// get thread context
				hImc = ImmGetContext(hWnd);
				// 조합중인 문자의 필요 버퍼크기를 구한다.
				length = ImmGetCompositionString(hImc, GCS_COMPSTR, NULL, 0);
				tmpComp = (char*)alloca(length + 1);
				ImmGetCompositionString(hImc, GCS_COMPSTR, tmpComp, length);
				tmpComp[length] = NULL;
				// 여기서 한글 조립 해야됨
				if (isKorean)
				{
					offset -= 2;
					Delete(offset, 2);
				}
				// backspace 에 대한 처리
				length ? isKorean = true : isKorean = false;
				Insert(offset, tmpComp);
				offset += length;
				ImmReleaseContext(hWnd, hImc); // release hanlde
				InvalidateRect(hWnd, NULL, true); // make wm_paint message
				SetCaret();
			}
			break; // must be break
		}

		return 0;
	}

	LRESULT Ime::imeChar(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
	{
		switch (iMessage)
		{
		case WM_IME_CHAR:
			// 스페이스, 숫자등도 이 메세지를 받기 때문에 DBCS 인지 SBCS인지 검사해야함
			if (isDBCS((byte)(wParam >> 8)))
			{
				tmpChar[0] = HIBYTE(LOWORD(wParam));
				tmpChar[1] = LOBYTE(LOWORD(wParam));
				tmpChar[2] = 0;
			}
			else // means SBCS
			{
				tmpChar[0] = (byte)wParam;
				tmpChar[1] = 0;
			}
			if (isKorean)
			{
				offset -= 2;
				Delete(offset, 2);
			}
			Insert(offset, tmpChar);
			offset += strlen(tmpChar);
			isKorean = false;
			InvalidateRect(hWnd, NULL, true); // make wm_paint message
			SetCaret();
			return 0; // must be return 0
		}

		return 0;
	}

	LRESULT Ime::wmSetFocus(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
	{
		switch (iMessage)
		{
		case WM_SETFOCUS:
			//SetCaret();
			break;
		}

		return 0;
	}

	LRESULT Ime::wmKillFocus(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
	{
		switch (iMessage)
		{
		case WM_KILLFOCUS:
			//DestroyCaret();
			break;
		}

		return 0;
	}

	LRESULT Ime::wmKeyDown(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
	{
		switch (iMessage)
		{
		case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_LEFT:
				if (offset > 0)
				{
					offset = GetPrevOff(offset);
					SetCaret();
				}
				return 0;
			case VK_RIGHT:
				if (offset < (int)strlen(buf))
				{
					offset = GetNextOff(offset);
					SetCaret();
				}
				return 0;
			case VK_HOME:
				offset = 0;
				SetCaret();
				return 0;
			case VK_END:
				offset = (int)strlen(buf);
				SetCaret();
				return 0;
			case VK_DELETE:
				if (isDBCS(offset))
					Delete(offset, 2);
				else
					Delete(offset, 1);
				InvalidateRect(hWnd, NULL, true);
				return 0;
			case VK_BACK:
				if (offset == 0)
					return 0;
				offset = GetPrevOff(offset);
				SendMessage(hWnd, WM_KEYDOWN, VK_DELETE, 0);
				SetCaret();
				return 0;
			}
			break;
		}

		return 0;
	}
}
