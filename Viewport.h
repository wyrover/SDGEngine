// 2014-03-16 ~ 2014-03-18
#pragma once

namespace SDGEngine
{
	class TileMap;
	class Viewport : public Singleton<Viewport>
	{
	public:
		Viewport() {}
		virtual ~Viewport() {}

		void Init(TileMap *mapinfo, int ViewportW, int ViewportH);
		void Update(float delta);
		void Render();

	private:
		Rect m_ViewPort;
		Rect m_TotalMapSize;
		TileMap *m_TileMapInfo = NULL;
		int m_ViewportX;
		int m_ViewportY;
		const float MoveUnit = 1000.0f;
		DISALLOW_COPY_AND_ASSIGN(Viewport);
	};
}
