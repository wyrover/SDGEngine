#pragma once

namespace sidescroll
{
	class Sprite
	{
	public:
		Sprite();
		Sprite(const std::string &filename);
		~Sprite();

		void Render();

	private:
		Bounds m_bounds;
		TextureAsset *texture = nullptr;
		unsigned int width, height;
		D3DXVECTOR2 textureOffset;
		D3DXVECTOR2 textureScale;
	};
}
