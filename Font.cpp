#include "Precompiled.h"

Font::Font(std::string pfontName, int size, D3DCOLOR color)
{
	m_fontName = pfontName;
	m_fontSize = size;
	m_fontColor = color;

	if (FAILED(D3DXCreateFont(ENGINE->device(), m_fontSize, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, m_fontName.c_str(), &m_Font)))
		std::cout << "can not create Font: " << m_fontName.c_str() << std::endl;
}

Font::~Font()
{
	SRELEASE(m_Font);
}

int Font::PrintFormat(int x, int y, char* str, ...)
{
	RECT rc;
	SetRect(&rc, x, y, -1, -1);
	// 가변인자
	va_list ap;
	INT nLenResult = 0;
	TCHAR Buffer[256];

	// 읽어들임
	va_start(ap, str);
	{
		// 버퍼에 기록
		nLenResult = wvsprintf(Buffer, str, ap);
	}
	va_end(ap);

	m_Font->DrawText(NULL, Buffer, -1, &rc, DT_NOCLIP | DT_VCENTER, m_fontColor);

	return nLenResult;
}

bool Font::HasCharacter(char c)
{
	return false;
}