#include "Precompiled.h"

namespace sidescroll
{
	void Graphics::BindTexture(TextureAsset *texture)
	{
		ENGINE->device()->SetTexture(0, texture->texture() ? texture->texture() : nullptr);
	}

	void Graphics::RenderQuad(unsigned w, unsigned h, D3DXVECTOR2 off, D3DXVECTOR2 scale)
	{

	}
	
	void Graphics::RenderBox(D3DXVECTOR2 min, D3DXVECTOR2 max)
	{
		BoundsVerts verts[5];
		/*
			0-------1
			|		|
			|		|
			3-------2
		*/
		verts[0].x = min.x;
		verts[0].y = min.y;
		verts[1].x = max.x;
		verts[1].y = min.y;
		verts[2].x = max.x;
		verts[2].y = max.y;
		verts[3].x = min.x;
		verts[3].y = max.y;
		verts[4].x = min.x;
		verts[4].y = min.y;

		//float Top = ((float)m_rtTexture.top) / m_pTexture->GetImageH();
		//float Bottom = ((float)m_rtTexture.bottom) / m_pTexture->GetImageH();
		//float Left = ((float)m_rtTexture.left) / m_pTexture->GetImageW();
		//float Right = ((float)m_rtTexture.right) / m_pTexture->GetImageW();

		//verts[0].tu = min.x;
		//verts[0].tv = min.y;
		//verts[1].tu = max.x;
		//verts[1].tv = min.y;
		//verts[2].tu = max.x;
		//verts[2].tu = max.y;
		//verts[3].tu = min.x;
		//verts[3].tu = max.y;

		ENGINE->device()->SetFVF(BoundsVerts::BoundsFvF);
		ENGINE->device()->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, verts, sizeof(BoundsVerts));
	}

	void Graphics::SetAlphatest(bool flag)
	{
		if (flag)
		{
			ENGINE->device()->SetRenderState(D3DRS_ALPHATESTENABLE, true);
			ENGINE->device()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);
			ENGINE->device()->SetRenderState(D3DRS_ALPHAREF, 0);
		}
		else
		{
			ENGINE->device()->SetRenderState(D3DRS_ALPHATESTENABLE, false);
		}
	}
}