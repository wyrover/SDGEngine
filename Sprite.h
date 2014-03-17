#pragma once

namespace SDGEngine
{
	class Sprite
	{
	public:
		Sprite();
		explicit Sprite(const std::string &filename);
		~Sprite();

		void Render();
		void setOffPosition(float x, float y);
		void setPosition(float x, float y);

	private:
		TextureAsset *m_texture = NULL;
		unsigned int width, height;
		D3DXVECTOR2 textureOffset;
		D3DXVECTOR2 textureScale;
		D3DXVECTOR2 position;
		DISALLOW_COPY_AND_ASSIGN(Sprite);
	};
}
