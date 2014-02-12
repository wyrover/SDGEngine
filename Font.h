#pragma once

class Font
{
public:
	Font(std::string pfontName, int size, D3DCOLOR color = D3DXCOLOR(0, 0, 0, 1));
	~Font();

	int PrintFormat(int x, int y, char* str, ...);
	bool HasCharacter(char c);

private:
	ID3DXFont* m_Font;
	std::string	 m_fontName;
	int m_fontSize;
	D3DCOLOR m_fontColor;
};
