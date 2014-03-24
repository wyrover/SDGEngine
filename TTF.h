#pragma once

namespace SDGEngine
{
	struct GlyphData {
		// 문자 출력에 필요한 여러가지 값
		int bwidth = 0, bheight = 0; // face->glyph->bitmap.width, face->glyph->bitmap.rows
		int advance_x = 0, advance_y = 0; // face->glyph->addvance.x, face->glyph->addvance.y 26.6포인트이므로 64로 나누어야함(>>6)
		int bitmap_left = 0, bitmap_top = 0; // face->glyph->bitmap_left, face->glyph->bitmap_top (top은 - 값으로 저장됨), 베어링
		TextureAsset *m_texture = NULL;
	};

	class TTF
	{
	public:
		TTF(std::string fontname, int size);
		~TTF();

		GlyphData *getChar(char c);
		int RenderText(int x, int y, const char *str, ...);

	private:
		// 글자 하나를 캐쉬한다.
		std::map<int, GlyphData *> m_glyphData;
		// FreeType 라이브러리
		FT_Library m_library;
		// 폰트 페이스
		FT_Face m_face;
		// 폰트 사이즈
		int m_fontsize;
		// 로드된 폰트 이름
		std::string m_fontname;
	};
}
