#include "Precompiled.h"

namespace sidescroll
{
	void Graphics::BindTexture(TextureAsset *texture)
	{
		if (texture)
			MySingleton<Engine>::GetSingleton()->Device()->SetTexture(0, texture->texture() ? texture->texture() : nullptr);
		else
			MySingleton<Engine>::GetSingleton()->Device()->SetTexture(0, nullptr);
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
		float halfWidth = textureScale.x*0.5f;
		float halfHeight = textureScale.y*0.5f;

		float Left = (textureOffset.x + 0.5f) / w;
		float Top = (textureOffset.y + 0.5f) / h;
		float Right = (textureOffset.x + textureScale.x + 0.5f) / w;
		float Bottom = (textureOffset.y + textureScale.y + 0.5f) / h;

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

		MySingleton<Engine>::GetSingleton()->Device()->SetFVF(BoundsVerts::FvF);
		MySingleton<Engine>::GetSingleton()->Device()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, verts, sizeof(BoundsVerts));
	}

	void Graphics::RenderLine(const D3DXVECTOR2& pos1, const D3DXVECTOR2 &pos2)
	{
		static GeneralVerts verts[2];

		verts[0].x = pos1.x;
		verts[0].y = pos1.y;
		verts[1].x = pos2.x;
		verts[1].y = pos2.y;

		MySingleton<Engine>::GetSingleton()->Device()->SetFVF(GeneralVerts::FvF);
		MySingleton<Engine>::GetSingleton()->Device()->DrawPrimitiveUP(D3DPT_LINESTRIP, 2, verts, sizeof(GeneralVerts));
	}

	void Graphics::RenderLineRect(float x, float y, float w, float h)
	{
		/*
		0,4-----1
		|		|
		|		|
		3-------2
		*/
		static GeneralVerts verts[5];

		verts[0].x = x;
		verts[0].y = y;
		verts[1].x = x+w;
		verts[1].y = y;
		verts[2].x = x+w;
		verts[2].y = y+h;
		verts[3].x = x;
		verts[3].y = y+h;
		verts[4].x = x;
		verts[4].y = y;

		MySingleton<Engine>::GetSingleton()->Device()->SetFVF(GeneralVerts::FvF);
		MySingleton<Engine>::GetSingleton()->Device()->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, verts, sizeof(GeneralVerts));
	}

	void Graphics::RenderTriangle(float size)
	{
		static GeneralVerts vets[3];

		
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
			MySingleton<Engine>::GetSingleton()->Device()->SetRenderState(D3DRS_ALPHATESTENABLE, true);
			MySingleton<Engine>::GetSingleton()->Device()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);
			MySingleton<Engine>::GetSingleton()->Device()->SetRenderState(D3DRS_ALPHAREF, 0);
		}
		else
			MySingleton<Engine>::GetSingleton()->Device()->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	}

	void Graphics::SetAddressModes(D3DTEXTUREADDRESS address)
	{
		// WRAP, BORDER, CLAMP, MIRROR
		MySingleton<Engine>::GetSingleton()->Device()->SetSamplerState(0, D3DSAMP_ADDRESSU, address);
		MySingleton<Engine>::GetSingleton()->Device()->SetSamplerState(0, D3DSAMP_ADDRESSV, address);
		if (address == D3DTADDRESS_BORDER)
			MySingleton<Engine>::GetSingleton()->Device()->SetSamplerState(0, D3DSAMP_BORDERCOLOR, 0x000000ff);
	}

	void Graphics::SetTextureFilter(D3DTEXTUREFILTERTYPE texfilter)
	{
		// POINT, LINEAR, ANISOTROPIC
		MySingleton<Engine>::GetSingleton()->Device()->SetSamplerState(0, D3DSAMP_MAGFILTER, texfilter);
		MySingleton<Engine>::GetSingleton()->Device()->SetSamplerState(0, D3DSAMP_MINFILTER, texfilter);
	}

	void Graphics::SetMipmapFilter(D3DTEXTUREFILTERTYPE mipfilter)
	{
		// NONE, POINT, LINEAR
		MySingleton<Engine>::GetSingleton()->Device()->SetSamplerState(0, D3DSAMP_MIPFILTER, mipfilter);
	}

	void Graphics::SetTextureAlphaChannel()
	{
		MySingleton<Engine>::GetSingleton()->Device()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		MySingleton<Engine>::GetSingleton()->Device()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	}

	void Graphics::SetShadeAlphaChannel()
	{
		MySingleton<Engine>::GetSingleton()->Device()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
		MySingleton<Engine>::GetSingleton()->Device()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	}
}