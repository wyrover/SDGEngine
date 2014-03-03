#include "Precompiled.h"

namespace sidescroll
{
	void Graphics::BindTexture(TextureAsset *texture)
	{
		if (texture)
			ENGINE->device()->SetTexture(0, texture->texture() ? texture->texture() : nullptr);
		else
			ENGINE->device()->SetTexture(0, nullptr);
	}

	void Graphics::RenderQuad(unsigned w, unsigned h, const D3DXVECTOR2 &textureOffset, const D3DXVECTOR2 &textureScale, const D3DXVECTOR2 &position)
	{
		/*
		0-------1
		|		|
		|		|
		2-------3
		*/
		static BoundsVerts verts[4];
		float halfWidth = w*0.5f;
		float halfHeight = h*0.5f;

		float Top = textureOffset.y;
		float Bottom = textureScale.y / h;
		float Left = textureOffset.x;
		float Right = textureScale.x / w;

		// UL
		verts[0].tu = Left;
		verts[0].tv = Top;
		verts[0].x = -halfWidth + position.x;
		verts[0].y = -halfHeight + position.y;

		//UR
		verts[1].tu = Right;
		verts[1].tv = Top;
		verts[1].x = halfWidth + position.x;
		verts[1].y = -halfHeight + position.y;

		//LR
		verts[2].tu = Left;
		verts[2].tv = Bottom;
		verts[2].x = -halfWidth + position.x;
		verts[2].y = halfHeight + position.y;

		//LL
		verts[3].tu = Right;
		verts[3].tv = Bottom;
		verts[3].x = halfWidth + position.x;
		verts[3].y = halfHeight + position.y;

		ENGINE->device()->SetFVF(BoundsVerts::BoundsFvF);
		ENGINE->device()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, verts, sizeof(BoundsVerts));
	}

	int Graphics::RenderText(const FontAsset &font, int x, int y, char *str, ...)
	{
		RECT rc;
		SetRect(&rc, x, y, -1, -1);
		// 가변인자
		va_list ap;
		INT nLenResult = 0;
		TCHAR Buffer[256];

		// 읽어들임
		va_start(ap, str);
		{
			// 버퍼에 기록
			nLenResult = wvsprintf(Buffer, str, ap);
		}
		va_end(ap);

		font.getFont()->DrawText(NULL, Buffer, -1, &rc, DT_NOCLIP | DT_VCENTER, font.getColor());

		return nLenResult;
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
			ENGINE->device()->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	}

	void Graphics::SetAddressModes(D3DTEXTUREADDRESS address)
	{
		// WRAP, BORDER, CLAMP, MIRROR
		ENGINE->device()->SetSamplerState(0, D3DSAMP_ADDRESSU, address);
		ENGINE->device()->SetSamplerState(0, D3DSAMP_ADDRESSV, address);
		if (address == D3DTADDRESS_BORDER)
			ENGINE->device()->SetSamplerState(0, D3DSAMP_BORDERCOLOR, 0x000000ff);
	}

	void Graphics::SetTextureFilter(D3DTEXTUREFILTERTYPE texfilter)
	{
		// POINT, LINEAR, ANISOTROPIC
		ENGINE->device()->SetSamplerState(0, D3DSAMP_MAGFILTER, texfilter);
		ENGINE->device()->SetSamplerState(0, D3DSAMP_MINFILTER, texfilter);
	}

	void Graphics::SetMipmapFilter(D3DTEXTUREFILTERTYPE mipfilter)
	{
		// NONE, POINT, LINEAR
		ENGINE->device()->SetSamplerState(0, D3DSAMP_MIPFILTER, mipfilter);
	}

	void Graphics::SetTextureAlphaChannel()
	{
		ENGINE->device()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		ENGINE->device()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	}

	void Graphics::SetShadeAlphaChannel()
	{
		ENGINE->device()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
		ENGINE->device()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	}
}