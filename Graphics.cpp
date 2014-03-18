#include "Precompiled.h"

namespace SDGEngine
{
	void Graphics::BindTexture(TextureAsset *texture)
	{
		if (texture)
			Singleton<Engine>::GetSingleton()->Device()->SetTexture(0, texture->texture() ? texture->texture() : NULL);
		else
			Singleton<Engine>::GetSingleton()->Device()->SetTexture(0, NULL);
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

		float Left = (textureOffset.x + 0.5f) / w;
		float Top = (textureOffset.y + 0.5f) / h;
		float Right = (textureOffset.x + textureScale.x + 0.5f) / w;
		float Bottom = (textureOffset.y + textureScale.y + 0.5f) / h;

		// UL
		verts[0].tu = Left;
		verts[0].tv = Top;
		verts[0].x = position.x;
		verts[0].y = position.y;

		//UR
		verts[1].tu = Right;
		verts[1].tv = Top;
		verts[1].x = position.x + textureScale.x;
		verts[1].y = position.y;

		//LR
		verts[2].tu = Left;
		verts[2].tv = Bottom;
		verts[2].x = position.x;
		verts[2].y = position.y + textureScale.y;

		//LL
		verts[3].tu = Right;
		verts[3].tv = Bottom;
		verts[3].x = position.x + textureScale.x;
		verts[3].y = position.y + textureScale.y;

		Singleton<Engine>::GetSingleton()->Device()->SetFVF(BoundsVerts::FvF);
		Singleton<Engine>::GetSingleton()->Device()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, verts, sizeof(BoundsVerts));
	}

	void Graphics::RenderLine(const D3DXVECTOR2& pos1, const D3DXVECTOR2 &pos2)
	{
		static GeneralVerts verts[2];

		verts[0].x = pos1.x;
		verts[0].y = pos1.y;
		verts[1].x = pos2.x;
		verts[1].y = pos2.y;

		Singleton<Engine>::GetSingleton()->Device()->SetFVF(GeneralVerts::FvF);
		Singleton<Engine>::GetSingleton()->Device()->DrawPrimitiveUP(D3DPT_LINESTRIP, 2, verts, sizeof(GeneralVerts));
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

		Singleton<Engine>::GetSingleton()->Device()->SetFVF(GeneralVerts::FvF);
		Singleton<Engine>::GetSingleton()->Device()->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, verts, sizeof(GeneralVerts));
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
			Singleton<Engine>::GetSingleton()->Device()->SetRenderState(D3DRS_ALPHATESTENABLE, true);
			Singleton<Engine>::GetSingleton()->Device()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);
			Singleton<Engine>::GetSingleton()->Device()->SetRenderState(D3DRS_ALPHAREF, 0);
		}
		else
			Singleton<Engine>::GetSingleton()->Device()->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	}

	void Graphics::SetAddressModes(D3DTEXTUREADDRESS address)
	{
		// WRAP, BORDER, CLAMP, MIRROR
		Singleton<Engine>::GetSingleton()->Device()->SetSamplerState(0, D3DSAMP_ADDRESSU, address);
		Singleton<Engine>::GetSingleton()->Device()->SetSamplerState(0, D3DSAMP_ADDRESSV, address);
		if (address == D3DTADDRESS_BORDER)
			Singleton<Engine>::GetSingleton()->Device()->SetSamplerState(0, D3DSAMP_BORDERCOLOR, 0x000000ff);
	}

	void Graphics::SetTextureFilter(D3DTEXTUREFILTERTYPE texfilter)
	{
		// POINT, LINEAR, ANISOTROPIC
		Singleton<Engine>::GetSingleton()->Device()->SetSamplerState(0, D3DSAMP_MAGFILTER, texfilter);
		Singleton<Engine>::GetSingleton()->Device()->SetSamplerState(0, D3DSAMP_MINFILTER, texfilter);
	}

	void Graphics::SetMipmapFilter(D3DTEXTUREFILTERTYPE mipfilter)
	{
		// NONE, POINT, LINEAR
		Singleton<Engine>::GetSingleton()->Device()->SetSamplerState(0, D3DSAMP_MIPFILTER, mipfilter);
	}

	void Graphics::SetTextureAlphaChannel()
	{
		Singleton<Engine>::GetSingleton()->Device()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		Singleton<Engine>::GetSingleton()->Device()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	}

	void Graphics::SetShadeAlphaChannel()
	{
		Singleton<Engine>::GetSingleton()->Device()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
		Singleton<Engine>::GetSingleton()->Device()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	}
}