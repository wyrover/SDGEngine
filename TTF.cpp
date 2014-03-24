#include "Precompiled.h"

namespace SDGEngine
{
	TTF::TTF(std::string fontname, int size)
		: m_fontsize(size), m_fontname(fontname)
	{
		int error = 0;
		// freetype �ε�
		error = FT_Init_FreeType(&m_library);
		if (error) std::cout << "FT_Init_FreeType Error" << std::endl;
		// ��Ʈ�йи��� ���̽��� �ε�
		error = FT_New_Face(m_library, fontname.c_str(), 0, &m_face);
		if (error) std::cout << "FT_New_Face Error" << std::endl;
		// ������ ����
		error = FT_Set_Char_Size(m_face, m_fontsize << 6, 0, GetDeviceCaps(NULL, LOGPIXELSX), GetDeviceCaps(NULL, LOGPIXELSY));
		if (error) std::cout << "FT_Set_Char_Size Error" << std::endl;
		// ����
		m_glyphData.clear();
	}

	TTF::~TTF()
	{
		// ����
		for (auto i : m_glyphData) {
			SDELETE(i.second->m_texture);
			SDELETE(i.second);
		}
		FT_Done_Face(m_face);
		FT_Done_FreeType(m_library);
	}

	GlyphData *TTF::getChar(char c)
	{
		// ������ �Ѿ�� �ƿ�
		if (c < 0 || c >= 65536)
			return NULL;
		// ĳ�� Ȯ��
		auto i = m_glyphData.find(c);
		if (i != m_glyphData.end())
			return i->second;
		//
		int error = 0;
		FT_Load_Char(m_face, c, FT_LOAD_RENDER | FT_LOAD_NO_BITMAP);
		if (error) // ��Ʈ ���̽��� ���� ���ڰ��̴�. ���� �ڵ鸵 �ʿ�
			return NULL;
		// ĳ�� �����Ϳ� ����. �׷��� ������!
		GlyphData *data = new GlyphData;
		data->bwidth = m_face->glyph->bitmap.width * m_fontsize;
		data->bheight = m_face->glyph->bitmap.rows * m_fontsize;
		data->bitmap_left = m_face->glyph->bitmap_left;
		data->bitmap_top = m_face->glyph->bitmap_top;
		data->advance_x = m_face->glyph->advance.x >> 6;
		data->advance_y = m_face->glyph->advance.y >> 6;

		// �ؽ���  ����
		data->m_texture = new TextureAsset;
		data->m_texture->LoadDynamic(data->bwidth, data->bheight);
		// �ؽ��Ŀ� ���
		D3DLOCKED_RECT rect;
		data->m_texture->texture()->LockRect(0, &rect, 0, D3DLOCK_DISCARD);
		DWORD *pBits = (DWORD*)rect.pBits;
		for (int y = 0; y < data->bheight; ++y) {
			for (int x = 0; x < data->bwidth; ++x) {
				BYTE b = m_face->glyph->bitmap.buffer[y * data->bwidth + x];
				pBits[y * (rect.Pitch / 4) + x] = D3DCOLOR_ARGB(b, 255, 255, 255);
			}
		}
		data->m_texture->texture()->UnlockRect(NULL);
		// ĳ��
		m_glyphData[c] = data;

		return data;
	}

	int TTF::RenderText(int x, int y, const char *str, ...)
	{
		RECT rc;
		SetRect(&rc, x, y, -1, -1);
		// ��������
		va_list ap;
		int nLenResult = 0; // ���� ���� ����
		char Buffer[256];

		// �о����
		va_start(ap, str);
		// ���ۿ� ���
		nLenResult = wvsprintf(Buffer, str, ap);
		va_end(ap);

		Singleton<Engine>::GetSingleton()->Device()->SetRenderState(D3DRS_ALPHATESTENABLE, true);
		Singleton<Engine>::GetSingleton()->Device()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		Singleton<Engine>::GetSingleton()->Device()->SetRenderState(D3DRS_ALPHAREF, 0);

		Singleton<Engine>::GetSingleton()->Device()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		Singleton<Engine>::GetSingleton()->Device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		Singleton<Engine>::GetSingleton()->Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		Singleton<Engine>::GetSingleton()->Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		Singleton<Engine>::GetSingleton()->Device()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		// ��¥ ������
		for (int idx = 0; idx < strlen(Buffer); idx++) {
			// ������ �۸��� ��Ʈ�� ����
			GlyphData *glyph = getChar(Buffer[idx]);
			if (!glyph) break;
			Graphics::BindTexture(glyph->m_texture);
			Graphics::RenderQuad(glyph->bwidth, glyph->bheight,
				D3DXVECTOR2(0.f, 0.f), D3DXVECTOR2(glyph->bwidth, glyph->bheight), D3DXVECTOR2(x, y));
		}

		// ��ȯ
		return nLenResult;
	}
}