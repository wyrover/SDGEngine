#include "Precompiled.h"

namespace SDGEngine
{
	TTFFont::TTFFont(int width)
		: m_width(width)
	{
		FT_Init_FreeType(&m_library);
		m_tex = new TextureAsset;
		m_tex->LoadDynamic(width, width);
		m_used.resize((width / 4) * (width / 4));	// 4x4�� �� ������ ���
		m_lockedrect.pBits = NULL;
	}

	TTFFont::~TTFFont()
	{
		FT_Done_FreeType(m_library);
		SDELETE(m_tex);
	}

	int TTFFont::Lock()
	{
		//m_lockedrect�� ���õǾ����� ��� �̹� ���� �ɷ��ִ� �̴ϴ�.  
		if (m_lockedrect.pBits) return -1;
		m_tex->texture()->LockRect(0, &m_lockedrect, nullptr, 0);
		return 0;
	}

	void TTFFont::UnLock()
	{
		if (!m_lockedrect.pBits)return;
		m_tex->texture()->UnlockRect(0);
		m_lockedrect.pBits = nullptr;
	}

	bool TTFFont::IsOccupied(int x, int y, int w, int h) const
	{
		//�ؽ��� ���� �˻��Ͽ�, (x, y)���� (x+w, y+h)�� ���� �� �� ���̶� ������̸� false��ȯ�մϴ�.  
		if (x + w >= m_width / 4) return false;
		if (y + h >= m_width / 4) return false;

		for (int i = x; i < x + w; ++i)
		{
			for (int j = y; j < y + h; ++j)
			{
				if (MapAt(i, j)) return false;
			}
		}
		return true;
	}

	void TTFFont::Fill(int x, int y, int w, int h, char d)
	{
		//�ؽ��� ���� ä��ϴ�.  
		for (int i = x; i < x + w; ++i)
		{
			for (int j = y; j < y + h; ++j)
			{
				MapAt(i, j) = d;
			}
		}
	}

	std::pair<int, int> TTFFont::Find(int w, int h) const
	{
		// (w, h)ũ���� �簢���� �� �� �ִ� ������ ã���ϴ�.  
		for (int j = 0; j < m_width / 4; ++j)
		{
			for (int i = 0; i < m_width / 4; ++i)
			{
				if (IsOccupied(i, j, w, h))
				{
					return std::make_pair(i, j);
				}
			}
		}
		return std::make_pair(-1, -1);
	}

	TTFFont::GlyphData TTFFont::GetGlyph(FT_Face face, char chr, int size)
	{
		//ĳ�õ� �۸����� ������ �װ� ��ȯ�ϰ�, ������ �ؽ��Ŀ� ���ܼ� ��ȯ���ִ� �Լ��Դϴ�
		//�۸��� �������Դϴ�.  
		Glyph g = { face, chr, size };
		GlyphData gd = { 0, };
		//�۸����� ĳ�ÿ��� ã�ƿ�  
		auto it = m_data.find(g);
		if (it != m_data.end())
		{
			it->second.use = 1;
			return it->second;
			//���� �ִٸ�, �׳� �� ������ �����ϸ� ��  
		}
		//���� ���� �ؽ��Ŀ� ����� ĳ���ؾ߰���.  
		//���� chr�� �۸��� �ε����� ����ϴ�  
		FT_UInt ix = FT_Get_Char_Index(face, chr);
		//�ε����� 0�̶�°� ���ڰ� ���ٴ°ſ���. �׳� gd�� �����ϰ� ����  
		if (ix == 0)
		{
			return gd;
		}
		//�۸����� �о�鿩��.  
		if (FT_Load_Glyph(face, ix, FT_LOAD_RENDER | FT_LOAD_NO_BITMAP))
		{
			//�����ϸ� gd�� �����ϰ� ����  
			return gd;
		}
		//�۸����� ���� ������ �˾Ƴ��ϴ�.  
		gd.bmW = face->glyph->bitmap.width;
		gd.bmH = face->glyph->bitmap.rows;

		//�ش� ũ���� �۸����� �� ������ ã�ƿ�.  
		//�ؽ��� ���� 4x4�ȼ��� �� ������ �Ѵٰ� �׷�����,  
		//�ȼ������� bmW, bmH�� �� ������ �ٲ���߰���  
		//�׷��� 3�� ���ϰ� 4�� �����ſ���.  
		auto p = Find((gd.bmW + 3) / 4, (gd.bmH + 3) / 4);
		//�� ������ ������ �����Դϴ�.  
		if (p.first < 0) return gd;
		//�׷��� ������ ���� �� �ƾ��.  
		//������ ���� �Է��ϰ�  
		gd.advX = face->glyph->advance.x >> 6;
		gd.advY = face->glyph->advance.y >> 6;
		gd.height = face->height >> 6;
		gd.left = face->glyph->bitmap_left;
		gd.top = -face->glyph->bitmap_top;
		gd.u = p.first * 4 / (float)m_width;
		gd.v = p.second * 4 / (float)m_width;
		gd.w = gd.bmW / (float)m_width;
		gd.h = gd.bmH / (float)m_width;
		gd.use = 1;

		if (Lock() == 0)
		{
			//���� �ɾ  
			DWORD* pBits = (DWORD*)m_lockedrect.pBits;
			for (int j = 0; j < gd.bmH; ++j)
			{
				for (int i = 0; i < gd.bmW; ++i)
				{
					//�ؽ����� �ش� ������ �ȼ��� ���������. ���� �������, ���İ��� �������ָ� �˴ϴ�.  
					BYTE b = face->glyph->bitmap.buffer[i + j*gd.bmW];
					pBits[(i + p.first * 4) + (j + p.second * 4)*m_lockedrect.Pitch / 4] = D3DCOLOR_ARGB(b, 255, 255, 255);
				}
			}
			UnLock();
		}
		//���� �� ������ �۸����� ĳ�õǾ� ������, ������̶�� �ؽ��ĸʿ� ǥ�ø� �սô�  
		Fill(p.first, p.second, (gd.bmW + 3) / 4, (gd.bmH + 3) / 4);
		//�׸��� ĳ�ÿ� �۸��� ������ �־�ΰ�  
		m_data[g] = gd;
		//��ȯ�ϸ鼭 ��  
		return gd;
	}

	std::string TTFFont::PrepareGlyph(FT_Face face, const char *str, int len, int size)
	{
		//������ ���� �۸����� ĳ�����ִ� �Լ�����.  
		//�۸��� �����Ͱ� ��� ĳ������ ���� ���ڸ� ��� wstring���� ����� ��ȯ���ݴϴ�.  
		std::string ret;
		for (int t = 0; t < len; ++t)
		{
			//�۸����� �����ϱ���  
			Glyph g = { face, str[t], size };
			//�ϴ� ĳ�ÿ� �ֳ� ã�ƺ��ϴ�.  
			auto it = m_data.find(g);
			if (it != m_data.end())
			{
				//������ �������ڷ� �ǳʶٰ�  
				continue;
			}
			//�۸��� �ε����� ����  
			FT_UInt ix = FT_Get_Char_Index(face, str[t]);
			if (ix == 0)
			{
				//�ε����� 0�ΰ�, �۸����� ���ٴ� ����.  
				//��ȯ�� ��Ͽ� �߰�  
				ret.push_back(str[t]);
				continue;
			}
			//�۸����� �о����  
			if (FT_Load_Glyph(face, ix, FT_LOAD_RENDER | FT_LOAD_NO_BITMAP))
			{
				continue;
			}
			//���� ���⼭���ʹ� GetGlyph�Լ��� ���׿�  
			GlyphData gd = { 0, };
			gd.bmW = face->glyph->bitmap.width;
			gd.bmH = face->glyph->bitmap.rows;

			auto p = Find((gd.bmW + 3) / 4, (gd.bmH + 3) / 4);
			if (p.first < 0)
			{
				CleanUp();
				p = Find((gd.bmW + 3) / 4, (gd.bmH + 3) / 4);
				if (p.first < 0) continue;
			}

			gd.advX = face->glyph->advance.x >> 6;
			gd.advY = face->glyph->advance.y >> 6;
			gd.height = face->size->metrics.height >> 6;
			gd.left = face->glyph->bitmap_left;
			gd.top = -face->glyph->bitmap_top;
			gd.u = p.first * 4 / (float)m_width;
			gd.v = p.second * 4 / (float)m_width;
			gd.w = gd.bmW / (float)m_width;
			gd.h = gd.bmH / (float)m_width;
			gd.use = 0;

			//���� �� �ɷ������� �ɾ����  
			if (!m_lockedrect.pBits) Lock();

			DWORD* pBits = (DWORD*)m_lockedrect.pBits;
			for (int j = 0; j < gd.bmH; ++j)
			{
				for (int i = 0; i < gd.bmW; ++i)
				{
					BYTE b = face->glyph->bitmap.buffer[i + j*gd.bmW];
					pBits[(i + p.first * 4) + (j + p.second * 4)*m_lockedrect.Pitch / 4] = D3DCOLOR_ARGB(b, 255, 255, 255);
				}
			}
			Fill(p.first, p.second, (gd.bmW + 3) / 4, (gd.bmH + 3) / 4);
			m_data[g] = gd;
		}
		//������ ���� �ѹ��� �ɰ�, �ѹ��� Ǯ�� �ִ°Ŵ�, ������ �� ������ Ǯ���ִ°� ����  
		//�� �������� �� �ɰ� Ǯ�� �ݺ��ϸ� ���� �������ϴ�.  
		if (m_lockedrect.pBits) UnLock();
		return ret;
	}

	void TTFFont::CleanUp()
	{
		//������ �ʴ� �۸����� ��� ����������.  
		std::map<Glyph, GlyphData> ng;
		for (auto p : m_data)
		{
			if (p.second.use == 1)
			{
				//���̰� ������ ng�� �־�ΰ�  
				ng.insert(p);
			}
			else
			{
				//�׷��� ������ �� �ؽ��� ���� �����ϰ� ���������ϴ�. �滩����  
				Fill(p.second.u * m_width / 4, p.second.v * m_width / 4, (p.second.bmW + 3) / 4, (p.second.bmH + 3) / 4, 0);
			}
		}
		//�����ؼ� ������  
		m_data.swap(ng);
	}

	void TTFFont::NewFrame()
	{
		//���ο� �������� �����Ҷ� ȣ�����ݴϴ�.  
		//��� ĳ�õ� �۸����� ���Ƚ���� 0���� �����մϴ�.  
		for (auto& p : m_data)
		{
			p.second.use = 0;
		}
	}
}
