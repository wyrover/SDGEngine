#pragma once

namespace sidescroll
{
	class Graphics
	{
	public:
		Graphics() {}
		~Graphics() {}

		static void BindTexture(TextureAsset *texture);
		static void RenderQuad(unsigned w, unsigned h, D3DXVECTOR2 off, D3DXVECTOR2 scale);
		static void RenderBox(D3DXVECTOR2 min, D3DXVECTOR2 max);
		//static void RenderText(const FontAsset &font, std::string text, int x, int y);
		static void SetAlphatest(bool flag);

	private:

	};
}