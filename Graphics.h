#pragma once

namespace sidescroll
{
	struct BoundsVerts
	{
		float x, y, z = 0.f, rhw = 1.0f;
		float tu, tv;
		static const DWORD FvF = D3DFVF_XYZRHW | D3DFVF_TEX1;
	};

	struct GeneralVerts
	{
		float x, y, z = 0.f, rhw = 1.0f;
		DWORD color = Colours::Red;
		static const DWORD FvF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
	};

	class Graphics
	{
	public:
		Graphics() {}
		~Graphics() {}

		static void BindTexture(TextureAsset *texture);
		static void RenderQuad(unsigned w, unsigned h, const D3DXVECTOR2 &off, const D3DXVECTOR2 &scale, const D3DXVECTOR2 &position);
		static void RenderLine(const D3DXVECTOR2& pos1, const D3DXVECTOR2 &pos2);
		static void RenderLineRect(float x, float y, float w, float h);
		static void RenderTriangle(float size);
		static int  RenderText(const FontAsset &font, int x, int y, char *str, ...);
		static void SetAlphatest(bool flag);
		static void SetAddressModes(D3DTEXTUREADDRESS address);
		static void SetTextureFilter(D3DTEXTUREFILTERTYPE texfilter);
		static void SetMipmapFilter(D3DTEXTUREFILTERTYPE mipfilter);
		static void SetTextureAlphaChannel();
		static void SetShadeAlphaChannel();
	};
}