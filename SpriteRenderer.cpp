#include "Precompiled.h"

namespace sidescroll
{
	SpriteRenderer::SpriteRenderer()
	{
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}

	void SpriteRenderer::Init()
	{

	}

	void SpriteRenderer::Destroy()
	{

	}

	void SpriteRenderer::Update(float delta)
	{
		
	}

	void SpriteRenderer::Render()
	{
		//if (m_texture)
		//{
		//	float Top = ((float)m_rtTexture.top) / m_pTexture->GetImageH();
		//	float Bottom = ((float)m_rtTexture.bottom) / m_pTexture->GetImageH();
		//	float Left = ((float)m_rtTexture.left) / m_pTexture->GetImageW();
		//	float Right = ((float)m_rtTexture.right) / m_pTexture->GetImageW();

		//	if (m_bReverseX) std::swap(Left, Right);	//좌우 반전
		//	if (m_bReverseY) std::swap(Top, Bottom);	//상하 반전

		//	static D3DXVECTOR2 BoxToSetting[4];
		//	BoxToSetting[0] = D3DXVECTOR2(-pBox->mSize.x*0.5f + pBox->mCen.x, -pBox->mSize.y*0.5f + pBox->mCen.y);
		//	BoxToSetting[1] = D3DXVECTOR2(+pBox->mSize.x*0.5f + pBox->mCen.x, -pBox->mSize.y*0.5f + pBox->mCen.y);
		//	BoxToSetting[2] = D3DXVECTOR2(-pBox->mSize.x*0.5f + pBox->mCen.x, +pBox->mSize.y*0.5f + pBox->mCen.y);
		//	BoxToSetting[3] = D3DXVECTOR2(+pBox->mSize.x*0.5f + pBox->mCen.x, +pBox->mSize.y*0.5f + pBox->mCen.y);

		//	D3DXMATRIX tran;
		//	D3DXMatrixTranslation(&tran, pBox->mPos.x, pBox->mPos.y, 0.f);
		//	for (int i = 0; i<4; i++) D3DXVec2TransformCoord(&BoxToSetting[i], &BoxToSetting[i], &tran);

		//	SetImageElement(m_vtxImg[0], D3DXVECTOR4(BoxToSetting[0].x - 0.5f, BoxToSetting[0].y - 0.5f, 0.5f, 1.0f), Left, Top);
		//	SetImageElement(m_vtxImg[1], D3DXVECTOR4(BoxToSetting[1].x - 0.5f, BoxToSetting[1].y - 0.5f, 0.5f, 1.0f), Right, Top);
		//	SetImageElement(m_vtxImg[2], D3DXVECTOR4(BoxToSetting[2].x - 0.5f, BoxToSetting[2].y - 0.5f, 0.5f, 1.0f), Left, Bottom);
		//	SetImageElement(m_vtxImg[3], D3DXVECTOR4(BoxToSetting[3].x - 0.5f, BoxToSetting[3].y - 0.5f, 0.5f, 1.0f), Right, Bottom);

		//	//설정된 사각형 영역으로 그린다.
		//	//랜더상태를 설정한다.
		//	g_pApp->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		//	g_pApp->GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);
		//	g_pApp->GetDevice()->SetRenderState(D3DRS_ALPHAREF, 0);

		//	//텍스쳐 설정 및 그리기
		//	g_pApp->GetDevice()->SetTexture(0, (m_pTexture) ? m_pTexture->GetTexture() : 0);
		//	g_pApp->GetDevice()->SetFVF(_2DTextureVerts_FVF);
		//	g_pApp->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_vtxImg, sizeof(_2DTextureVerts));
		//	//알파 테스트 끄기
		//	g_pApp->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		//}
	}
}
