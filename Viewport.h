#pragma once

namespace SDGEngine
{
	class TileMap;
	class Viewport
	{
	public:
		Viewport(TileMap *mapinfo, const int ViewportW, const int ViewportH);
		~Viewport() {}

		void Update();
		void Render();

	private:
		RECT m_ViewPort;
		TileMap *m_TileMapInfo;
	};
}
