#pragma once

namespace sidescroll
{
	class TileSet
	{
	public:
		TileSet(const std::string &str, float scalex, float scaley, int layer);
		~TileSet();

		void Render();
		//void Update();

	private:
		TextureAsset *texture;
		unsigned int width, height;
		D3DXVECTOR2 textureOffset;
		D3DXVECTOR2 textureScale;
		D3DXVECTOR2 position;
		unsigned int *cellid;
		unsigned int layerNum, xwidth, yheight, windex, hindex;
	};
}
