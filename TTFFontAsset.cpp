#include "Precompiled.h"

namespace SDGEngine
{
	//TTFFontAsset::TTFFontAsset(ISData* font, size_t index)
	//	: Asset(AssetType::ASSET_TTF), m_height(8), m_scale(1)
	//{
	//	m_data = font;
	//	//�� ���� ��Ʈ�� �ִ� 3������ �� �� �־��.  
	//	//CSS���� ��ü��Ʈ�� ����ϴ� �� ����, �۸����� ���� ������ ��� ���� ��Ʈ�� ����� ����ϰ� �˴ϴ�  
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
	//	//��Ʈ�� ũ�⸦ �����ؿ�. �̶� m_face[0]->size ����ü�� ���õ˴ϴ�.  
	//	FT_Set_Pixel_Sizes(m_face[0], m_height * m_scale, m_height * m_scale);
	//	//���õ� size ����ü���� ũ�⿡ ���� ������ ����.  
	//	//���� �����Ҽ��� 26.6�������� �Ǿ������Ƿ� 64�� ����� float�� �ٲ�����մϴ�.  
	//	float fHeight = m_face[0]->size->metrics.height / 64.f;
	//	//��ü ��Ʈ�� ���� : �ٰ������� ����� �ſ���  
	//	float fAsc = m_face[0]->size->metrics.ascender / 64.f;
	//	//���� �����κ��� ���� �ö� �ִ� ���� : ��Ʈ ���̸� ���ߴµ� �߿��մϴ�.  
	//	float fDsc = m_face[0]->size->metrics.descender / 64.f;
	//	//���� �����κ��� �Ʒ��� ������ �ִ� ����  

	//	//�ؽ��Ŀ� ���İ� �� �����Ƿ�, �̰� �������ְ� ���ߵſ�.  
	//	//��Ʈ ����ϱ⿡ �ռ� �ѹ��� ����ϸ� ������, �װͱ��� �ϸ� �Ӹ����ñ�� �ϴ��� ���⿡ �Ĺھ� �����ϴ�.  
	//	m_pIS->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	//	m_pIS->GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//	m_pIS->GetDevice()->SetRenderState(D3DRS_ALPHAREF, 0);
	//	m_pIS->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//	m_pIS->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//	m_pIS->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//	m_pIS->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//	//�پ��� ������ ��Ʈ�� ����ϱ� ���ؼ� MODULATE!  
	//	//ISGlyphBank���� ���ڸ� ������� ����� ��ﳪ��?  
	//	//�ű⿡ COLOR�� �Ѿ�� ���ڸ� �����ָ� �پ��� ������ ���ڸ� ����� �� �ְԵǴ°���  
	//	m_pIS->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	//	//��Ʈ ����� ���� ��ġ�Դϴ�. x�� �ڽ��� ���ʺ���, y�� �ڽ��� ���ʿ��� fAsc��ŭ �����ͼ� ���ؼ��� ����ϴ�.  
	//	float x = rect->left, y = rect->top + fAsc;
	//	//�۸����� �غ��ؿ�.  
	//	std::wstring m2 = m_pIS->GetGlyphBank()->PrepareGlyph(m_face[0], str, wcslen(str), m_height * m_scale);
	//	if (m_face[1])
	//	{
	//		//���� ���� ��Ʈ�� �ִٸ� ���� ��Ʈ�� �����ϰ�, �۸����� ���� ���ڵ��� ������Ʈ���� �۸����� �غ��ϵ����մϴ�.  
	//		FT_Set_Pixel_Sizes(m_face[1], m_height * m_scale, m_height * m_scale);
	//		m2 = m_pIS->GetGlyphBank()->PrepareGlyph(m_face[1], m2.c_str(), m2.size(), m_height * m_scale);
	//		if (m_face[2])
	//		{
	//			FT_Set_Pixel_Sizes(m_face[2], m_height * m_scale, m_height * m_scale);
	//			m_pIS->GetGlyphBank()->PrepareGlyph(m_face[2], m2.c_str(), m2.size(), m_height * m_scale);
	//		}
	//	}

	//	//�ٺ� ���� ���̸� �����մϴ�.  
	//	std::vector<int> width;
	//	width.push_back(0);
	//	//���� ����� �� �̵��� �ϰ�, ���� ��Ʈ������ ����մϴ�.  
	//	//���� ��� �����̰ų�, ���� ��� ������ ��쿣 ������ ���� ���  
	//	if (format & DT_CENTER || format & DT_VCENTER)
	//	{
	//		for (LPCWSTR p = str; *p; ++p)
	//		{
	//			if (*p == '\n')
	//			{
	//				//�� �ٲ� ó��  
	//				width.push_back(0);
	//				continue;
	//			}
	//			//�۸��������͸� �����Ϳ�  
	//			ISGlyphBank::GlyphData gd = m_pIS->GetGlyphBank()->GetGlyph(m_face[0], *p, m_height * m_scale);
	//			if (gd.bmW == 0 && m_face[1])
	//			{
	//				gd = m_pIS->GetGlyphBank()->GetGlyph(m_face[1], *p, m_height * m_scale);
	//				if (gd.bmW == 0 && m_face[2])
	//				{
	//					gd = m_pIS->GetGlyphBank()->GetGlyph(m_face[2], *p, m_height * m_scale);
	//				}
	//			}

	//			//�� �ٿ� �� ����� �� ������, �ڵ� �ٹٲ��� ���ݴϴ�.  
	//			if (width.back() + gd.bmW + gd.left >= rect->right)
	//			{
	//				width.push_back(0);
	//			}
	//			//���� ����ŭ ���� ���̸� �÷���߰�����  
	//			width.back() += gd.advX;
	//		}
	//	}

	//	//��Ʈ���� ����� ��������, ���� ���� ��ġ�� �������غ��ô�.  

	//	//���� ��� ������ ��� x���� �����������  
	//	if (format & DT_CENTER)
	//	{
	//		x = (rect->right + rect->left - width[0]) / 2;
	//	}
	//	//���� ��� ������ ��� y���� �����������  
	//	if (format & DT_VCENTER)
	//	{
	//		y = (rect->bottom + rect->top - width.size() * fHeight) / 2 + fAsc;
	//	}

	//	//���� ��¥ ����Դϴ� ��  
	//	int line = 0;
	//	for (; *str; ++str)
	//	{
	//		if (*str == '\n')
	//		{
	//			//�ٹٲ� ó��  
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

	//		//���������� �� ����� �� ������, �ڵ� �ٹٲ�  
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
	//		//�ؽ��ĸ� ����ִ� ISI �޼ҵ��Դϴ�. ȭ�� ���� ��ǥ (x, y)�� ũ�� (w, h)�� �ް�,  
	//		//�ؽ��� UV�� UV���� w,h�� �ް�, ����� ������ �޾� ������ݴϴ�.  
	//		//�Ʒ��ʿ� �Լ� ��ü �־������ �����Ͻñ� �ٷ���.  
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
	//	//���� �ؽ����ӿ��� SetTexture ȣ���� �߻����� �ʵ���  
	//	//�ؽ��İ� �ٲ𶧸� SetTexture�� ȣ�����ִ� �Լ��Դϴ�.  
	//	SelectFVF(D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_DIFFUSE);
	//	//SetFVF�� ���� ȣ���ϸ� �طο��״�, �ٲ� ���� ȣ���ϵ���  
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
