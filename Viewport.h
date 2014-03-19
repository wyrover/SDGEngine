// 2014-03-16 ~ 2014-03-18
#pragma once

namespace SDGEngine
{
	class Sprite;
	class TileMap;
	class Viewport
	{
	public:
		Viewport(TileMap *mapinfo, int ViewportW, int ViewportH);
		~Viewport() {}

		void Update();
		void Render();

	private:
		Rect m_ViewPort;
		Rect m_TotalMapSize;
		TileMap *m_TileMapInfo;
		int m_ViewportX;
		int m_ViewportY;
		DISALLOW_COPY_AND_ASSIGN(Viewport);
	};
}
