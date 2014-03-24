#include "Precompiled.h"

namespace SDGEngine
{
	TTFFont::TTFFont(int width)
		: m_width(width)
	{
		FT_Init_FreeType(&m_library);
		m_tex = new TextureAsset;
		m_tex->LoadDynamic(width, width);
		m_used.resize((width / 4) * (width / 4));	// 4x4를 한 블럭으로 사용
		m_lockedrect.pBits = NULL;
	}

	TTFFont::~TTFFont()
	{
		FT_Done_FreeType(m_library);
		SDELETE(m_tex);
	}

	int TTFFont::Lock()
	{
		//m_lockedrect이 세팅되어있을 경우 이미 락이 걸려있는 겁니다.  
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
		//텍스쳐 맵을 검색하여, (x, y)에서 (x+w, y+h)의 공간 중 한 블럭이라도 사용중이면 false반환합니다.  
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
		//텍스쳐 맵을 채웁니다.  
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
		// (w, h)크기의 사각형이 들어갈 수 있는 공간을 찾습니다.  
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
		//캐시된 글리프가 있으면 그걸 반환하고, 없으면 텍스쳐에 새겨서 반환해주는 함수입니다
		//글리프 데이터입니다.  
		Glyph g = { face, chr, size };
		GlyphData gd = { 0, };
		//글리프를 캐시에서 찾아요  
		auto it = m_data.find(g);
		if (it != m_data.end())
		{
			it->second.use = 1;
			return it->second;
			//만약 있다면, 그냥 그 정보를 리턴하면 끝  
		}
		//없을 경우는 텍스쳐에 새기고 캐싱해야겠죠.  
		//문자 chr의 글리프 인덱스를 얻습니다  
		FT_UInt ix = FT_Get_Char_Index(face, chr);
		//인덱스가 0이라는건 문자가 없다는거에요. 그냥 gd를 리턴하고 훼일  
		if (ix == 0)
		{
			return gd;
		}
		//글리프를 읽어들여요.  
		if (FT_Load_Glyph(face, ix, FT_LOAD_RENDER | FT_LOAD_NO_BITMAP))
		{
			//실패하면 gd를 리턴하고 훼일  
			return gd;
		}
		//글리프에 대한 정보를 알아냅니다.  
		gd.bmW = face->glyph->bitmap.width;
		gd.bmH = face->glyph->bitmap.rows;

		//해당 크기의 글리프가 들어갈 공간을 찾아요.  
		//텍스쳐 맵은 4x4픽셀을 한 블럭으로 한다고 그랬으니,  
		//픽셀단위의 bmW, bmH를 블럭 단위로 바꿔줘야겠죠  
		//그래서 3을 더하고 4로 나눈거에요.  
		auto p = Find((gd.bmW + 3) / 4, (gd.bmH + 3) / 4);
		//빈 공간이 없으면 훼일입니다.  
		if (p.first < 0) return gd;
		//그렇지 않으면 이제 다 됐어요.  
		//나머지 정보 입력하고  
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
			//락을 걸어서  
			DWORD* pBits = (DWORD*)m_lockedrect.pBits;
			for (int j = 0; j < gd.bmH; ++j)
			{
				for (int i = 0; i < gd.bmW; ++i)
				{
					//텍스쳐의 해당 지점의 픽셀을 설정해줘요. 색은 흰색으로, 알파값만 조절해주면 됩니다.  
					BYTE b = face->glyph->bitmap.buffer[i + j*gd.bmW];
					pBits[(i + p.first * 4) + (j + p.second * 4)*m_lockedrect.Pitch / 4] = D3DCOLOR_ARGB(b, 255, 255, 255);
				}
			}
			UnLock();
		}
		//이제 이 공간은 글리프가 캐시되어 있으니, 사용중이라고 텍스쳐맵에 표시를 합시다  
		Fill(p.first, p.second, (gd.bmW + 3) / 4, (gd.bmH + 3) / 4);
		//그리고 캐시에 글리프 정보를 넣어두고  
		m_data[g] = gd;
		//반환하면서 끝  
		return gd;
	}

	std::string TTFFont::PrepareGlyph(FT_Face face, const char *str, int len, int size)
	{
		//사전에 문자 글리프를 캐싱해주는 함수에요.  
		//글리프 데이터가 없어서 캐시하지 못한 문자를 모아 wstring으로 만들어 반환해줍니다.  
		std::string ret;
		for (int t = 0; t < len; ++t)
		{
			//글리프를 설정하구요  
			Glyph g = { face, str[t], size };
			//일단 캐시에 있나 찾아봅니다.  
			auto it = m_data.find(g);
			if (it != m_data.end())
			{
				//있으면 다음문자로 건너뛰고  
				continue;
			}
			//글리프 인덱스를 얻어요  
			FT_UInt ix = FT_Get_Char_Index(face, str[t]);
			if (ix == 0)
			{
				//인덱스가 0인건, 글리프가 없다는 거죠.  
				//반환할 목록에 추가  
				ret.push_back(str[t]);
				continue;
			}
			//글리프를 읽어오고  
			if (FT_Load_Glyph(face, ix, FT_LOAD_RENDER | FT_LOAD_NO_BITMAP))
			{
				continue;
			}
			//이제 여기서부터는 GetGlyph함수랑 같네요  
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

			//락이 안 걸려있으면 걸어줘요  
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
		//어차피 락은 한번만 걸고, 한번만 풀수 있는거니, 루프를 다 돌고나서 풀어주는게 좋죠  
		//매 루프마다 락 걸고 풀고 반복하면 무지 느려집니다.  
		if (m_lockedrect.pBits) UnLock();
		return ret;
	}

	void TTFFont::CleanUp()
	{
		//사용되지 않는 글리프를 모두 날려버려요.  
		std::map<Glyph, GlyphData> ng;
		for (auto p : m_data)
		{
			if (p.second.use == 1)
			{
				//쓰이고 있으면 ng에 넣어두고  
				ng.insert(p);
			}
			else
			{
				//그렇지 않으면 그 텍스쳐 맵을 과감하게 날려버립니다. 방빼야죠  
				Fill(p.second.u * m_width / 4, p.second.v * m_width / 4, (p.second.bmW + 3) / 4, (p.second.bmH + 3) / 4, 0);
			}
		}
		//스왑해서 마무리  
		m_data.swap(ng);
	}

	void TTFFont::NewFrame()
	{
		//새로운 프레임이 시작할때 호출해줍니다.  
		//모든 캐시된 글리프의 사용횟수를 0으로 설정합니다.  
		for (auto& p : m_data)
		{
			p.second.use = 0;
		}
	}
}
