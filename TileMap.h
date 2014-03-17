// 2014-03-16
#pragma once

namespace sidescroll
{
	class TextureAsset;
	class TileMap
	{
	public:
		TileMap(const std::string &path, const int width, const int height, int InMaxMapCellX, int InMaxMapCellY);
		~TileMap();

		RECT *GetCellRect(unsigned int cellid);
		RECT const *GetOneTileSize() const { return &m_FrameSize; }

		RECT *GetTile(int InX, int InY);
		int GetTileId(int InX, int InY) const;
		void CheckIsValidMapSize(int InX, int InY, int& OutX, int& OutY) const;

	private:
		bool CreateTiles();
		bool GetCellPos(const int InFrameNumber, RECT *OutTargetRect);

	private:
		std::vector<RECT *> m_TileSet;
		TextureAsset *m_TileTexture;	
		RECT m_FrameSize;		// 텍스쳐의 셀 하나당 가로,세로
		int m_FrameCount;		// m_MaxCellXCount * m_MaxCellYCount
		int m_MaxCellXCount;	// 텍스쳐의 x축 셀 개수
		int m_MaxCellYCount;	// 텍스쳐의 y축 셀 개수
		int m_MaxMapCellX;		// 전체 맵의 x셀 개수
		int m_MaxMapCellY;		// 전체 맵의 y셀 개수

		friend class Viewport;
	};
}
