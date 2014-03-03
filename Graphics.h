#pragma once

namespace sidescroll
{
	class Graphics
	{
	public:
		Graphics() {}
		~Graphics() {}

		static void BindTexture(TextureAsset *texture);
		static void RenderQuad(unsigned w, unsigned h, const D3DXVECTOR2 &off, const D3DXVECTOR2 &scale, const D3DXVECTOR2 &position);
		static int  RenderText(const FontAsset &font, int x, int y, char *str, ...);
		static void SetAlphatest(bool flag);
		static void SetAddressModes(D3DTEXTUREADDRESS address);
		static void SetTextureFilter(D3DTEXTUREFILTERTYPE texfilter);
		static void SetMipmapFilter(D3DTEXTUREFILTERTYPE mipfilter);
		static void SetTextureAlphaChannel();
		static void SetShadeAlphaChannel();
	};
}