#include "Precompiled.h"

namespace SDGEngine
{
	//TTFFontAsset::TTFFontAsset(ISData* font, size_t index)
	//	: Asset(AssetType::ASSET_TTF), m_height(8), m_scale(1)
	//{
	//	m_data = font;
	//	//한 놈이 폰트를 최대 3개까지 열 수 있어요.  
	//	//CSS에서 대체폰트를 사용하는 것 마냥, 글리프가 없는 문자일 경우 다음 폰트를 사용해 출력하게 됩니다  
	//	if (FT_New_Memory_Face(Singleton<TTFFont>::GetSingleton()->library(), 
	//		(const FT_Byte*)font->GetSrc(), font->GetSize(), index, &m_face)) {
	//		std::cout << "TTFFontAsset.cpp 14 line: FT_New_Memory_Face function failed!" << std::endl;
	//	}
	//}

	//TTFFontAsset::~TTFFontAsset()
	//{
	//	if (m_face)
	//	{
	//		FT_Done_Face(m_face);
	//		m_face = NULL;
	//	}
	//	SDELETE(m_data);
	//}
	// 
	//int TTFFontAsset::PrintText(char *str, RECT* rect, DWORD format, D3DXCOLOR color)
	//{
	//	//폰트의 크기를 설정해요. 이때 m_face[0]->size 구조체가 세팅됩니다.  
	//	FT_Set_Pixel_Sizes(m_face[0], m_height * m_scale, m_height * m_scale);
	//	//세팅된 size 구조체에서 크기에 대한 정보를 얻어내요.  
	//	//값은 고정소수점 26.6포맷으로 되어있으므로 64로 나누어서 float로 바꿔줘야합니다.  
	//	float fHeight = m_face[0]->size->metrics.height / 64.f;
	//	//전체 폰트의 높이 : 줄간격으로 사용할 거에요  
	//	float fAsc = m_face[0]->size->metrics.ascender / 64.f;
	//	//기준 선으로부터 위로 올라간 최대 높이 : 폰트 높이를 맞추는데 중요합니다.  
	//	float fDsc = m_face[0]->size->metrics.descender / 64.f;
	//	//기준 선으로부터 아래로 내려간 최대 높이  

	//	//텍스쳐에 알파가 들어가 있으므로, 이거 설정해주고 가야돼요.  
	//	//폰트 출력하기에 앞서 한번만 출력하면 되지만, 그것까지 하면 머리아플까봐 일단은 여기에 쳐박아 놨습니다.  
	//	m_pIS->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	//	m_pIS->GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//	m_pIS->GetDevice()->SetRenderState(D3DRS_ALPHAREF, 0);
	//	m_pIS->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//	m_pIS->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//	m_pIS->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//	m_pIS->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//	//다양한 색깔의 폰트를 출력하기 위해서 MODULATE!  
	//	//ISGlyphBank에서 글자를 흰색으로 썼던거 기억나죠?  
	//	//거기에 COLOR로 넘어가는 인자를 곱해주면 다양한 색으로 문자를 출력할 수 있게되는거죠  
	//	m_pIS->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	//	//폰트 출력의 시작 위치입니다. x는 박스의 왼쪽부터, y는 박스의 위쪽에서 fAsc만큼 내려와서 기준선에 맞춥니다.  
	//	float x = rect->left, y = rect->top + fAsc;
	//	//글리프를 준비해요.  
	//	std::wstring m2 = m_pIS->GetGlyphBank()->PrepareGlyph(m_face[0], str, wcslen(str), m_height * m_scale);
	//	if (m_face[1])
	//	{
	//		//만약 예비 폰트가 있다면 예비 폰트도 세팅하고, 글리프가 없는 문자들은 예비폰트에서 글리프를 준비하도록합니다.  
	//		FT_Set_Pixel_Sizes(m_face[1], m_height * m_scale, m_height * m_scale);
	//		m2 = m_pIS->GetGlyphBank()->PrepareGlyph(m_face[1], m2.c_str(), m2.size(), m_height * m_scale);
	//		if (m_face[2])
	//		{
	//			FT_Set_Pixel_Sizes(m_face[2], m_height * m_scale, m_height * m_scale);
	//			m_pIS->GetGlyphBank()->PrepareGlyph(m_face[2], m2.c_str(), m2.size(), m_height * m_scale);
	//		}
	//	}

	//	//줄별 가로 길이를 저장합니다.  
	//	std::vector<int> width;
	//	width.push_back(0);
	//	//실제 출력은 좀 이따가 하고, 먼저 매트릭스를 계산합니다.  
	//	//가로 가운데 정렬이거나, 세로 가운데 정렬일 경우엔 다음과 같이 계산  
	//	if (format & DT_CENTER || format & DT_VCENTER)
	//	{
	//		for (LPCWSTR p = str; *p; ++p)
	//		{
	//			if (*p == '\n')
	//			{
	//				//줄 바꿈 처리  
	//				width.push_back(0);
	//				continue;
	//			}
	//			//글리프데이터를 가져와요  
	//			ISGlyphBank::GlyphData gd = m_pIS->GetGlyphBank()->GetGlyph(m_face[0], *p, m_height * m_scale);
	//			if (gd.bmW == 0 && m_face[1])
	//			{
	//				gd = m_pIS->GetGlyphBank()->GetGlyph(m_face[1], *p, m_height * m_scale);
	//				if (gd.bmW == 0 && m_face[2])
	//				{
	//					gd = m_pIS->GetGlyphBank()->GetGlyph(m_face[2], *p, m_height * m_scale);
	//				}
	//			}

	//			//그 줄에 더 출력할 수 없으면, 자동 줄바꿈을 해줍니다.  
	//			if (width.back() + gd.bmW + gd.left >= rect->right)
	//			{
	//				width.push_back(0);
	//			}
	//			//문자 폭만큼 가로 길이를 늘려줘야겠지요  
	//			width.back() += gd.advX;
	//		}
	//	}

	//	//매트릭스 계산이 끝났으니, 문자 찍을 위치를 재정비해봅시다.  

	//	//가로 가운데 정렬일 경우 x값을 재조정해줘요  
	//	if (format & DT_CENTER)
	//	{
	//		x = (rect->right + rect->left - width[0]) / 2;
	//	}
	//	//세로 가운데 정렬일 경우 y값을 재조정해줘요  
	//	if (format & DT_VCENTER)
	//	{
	//		y = (rect->bottom + rect->top - width.size() * fHeight) / 2 + fAsc;
	//	}

	//	//이제 진짜 출력입니다 헤  
	//	int line = 0;
	//	for (; *str; ++str)
	//	{
	//		if (*str == '\n')
	//		{
	//			//줄바꿈 처리  
	//			++line;
	//			if (format & DT_CENTER)
	//			{
	//				x = ((rect->right + rect->left) - width[line]) / 2;
	//			}
	//			else
	//			{
	//				x = rect->left;
	//			}
	//			y += m_height;
	//			continue;
	//		}
	//		ISGlyphBank::GlyphData gd = m_pIS->GetGlyphBank()->GetGlyph(m_face[0], *str, m_height * m_scale);
	//		if (gd.bmW == 0 && m_face[1])
	//		{
	//			gd = m_pIS->GetGlyphBank()->GetGlyph(m_face[1], *str, m_height * m_scale);
	//			if (gd.bmW == 0 && m_face[2])
	//			{
	//				gd = m_pIS->GetGlyphBank()->GetGlyph(m_face[2], *str, m_height * m_scale);
	//			}
	//		}

	//		//오른쪽으로 더 출력할 수 없으면, 자동 줄바꿈  
	//		if (x + gd.bmW + gd.left >= rect->right)
	//		{
	//			++line;
	//			if (format & DT_CENTER && line < width.size())
	//			{
	//				x = ((rect->right + rect->left) - width[line]) / 2;
	//			}
	//			else
	//			{
	//				x = rect->left;
	//			}
	//			y += fHeight;
	//		}
	//		//텍스쳐를 찍어주는 ISI 메소드입니다. 화면 상의 좌표 (x, y)와 크기 (w, h)를 받고,  
	//		//텍스쳐 UV와 UV상의 w,h를 받고, 출력할 색상을 받아 출력해줍니다.  
	//		//아래쪽에 함수 몸체 넣어뒀으니 참고하시길 바래요.  
	//		DrawTexture(GetFTTexture(), x + gd.left, y + gd.top, gd.bmW, gd.bmH, gd.u, gd.v, gd.w, gd.h, color);
	//		x += gd.advX;
	//		y += gd.advY;
	//	}
	//	return 0;
	//}

	//void TTFFontAsset::DrawTexture(TextureAsset* texture, float destX, float destY, float destW, float destH,
	//	float srcU, float srcV, float srcW, float srcH, D3DCOLOR color)
	//{
	//	SelectTexture(texture->m_pTexture);
	//	//같은 텍스쳐임에도 SetTexture 호출이 발생하지 않도록  
	//	//텍스쳐가 바뀔때만 SetTexture를 호출해주는 함수입니다.  
	//	SelectFVF(D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_DIFFUSE);
	//	//SetFVF도 자주 호출하면 해로울테니, 바뀔 때만 호출하도록  
	//	struct {
	//		float x, y, z, w;
	//		D3DCOLOR c;
	//		float u, v;
	//	} v[4] = {
	//		{ destX + destW - .5f, destY - .5f, 0, 1.f, color, srcU + srcW, srcV, },
	//		{ destX - .5f, destY - .5f, 0, 1.f, color, srcU, srcV, },
	//		{ destX + destW - .5f, destY + destH - .5f, 0, 1.f, color, srcU + srcW, srcV + srcH, },
	//		{ destX - .5f, destY + destH - .5f, 0, 1.f, color, srcU, srcV + srcH, },
	//	};

	//	m_pd3dd->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, 28);
	//}

	//void TTFFontAsset::Reload()
	//{

	//}

	//void TTFFontAsset::Unload()
	//{

	//}
}
