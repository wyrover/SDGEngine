#pragma once

namespace SDGEngine
{
	struct GlyphData {
		// ���� ��¿� �ʿ��� �������� ��
		int bwidth = 0, bheight = 0; // face->glyph->bitmap.width, face->glyph->bitmap.rows
		int advance_x = 0, advance_y = 0; // face->glyph->addvance.x, face->glyph->addvance.y 26.6����Ʈ�̹Ƿ� 64�� ���������(>>6)
		int bitmap_left = 0, bitmap_top = 0; // face->glyph->bitmap_left, face->glyph->bitmap_top (top�� - ������ �����), ���
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
		// ���� �ϳ��� ĳ���Ѵ�.
		std::map<int, GlyphData *> m_glyphData;
		// FreeType ���̺귯��
		FT_Library m_library;
		// ��Ʈ ���̽�
		FT_Face m_face;
		// ��Ʈ ������
		int m_fontsize;
		// �ε�� ��Ʈ �̸�
		std::string m_fontname;
	};
}
