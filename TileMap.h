// 2014-03-16 ~ 2014-03-18
#pragma once

namespace SDGEngine
{
	class TextureAsset;
	class TileMap
	{
	public:
		TileMap(const std::string &path, const float width, const float height, int InMaxMapCellX, int InMaxMapCellY);
		~TileMap();

		Rect *GetTile(int InX, int InY);
		Rect GetOneTileSize() const { return m_FrameSize; }
		int TotalMapX() const { return m_MaxMapCellX; }
		int TotalMapY() const { return m_MaxMapCellY; }

	private:
		Rect *GetCellRect(unsigned int cellid);
		int GetTileId(int InX, int InY) const;
		void CheckIsValidMapSize(int InX, int InY, int& OutX, int& OutY) const;
		void CreateTiles();
		void GetCellPos(const int InFrameNumber, Rect *OutTargetRect);

	private:
		std::vector<Rect *> m_TileSet;
		TextureAsset *m_TileTexture;	
		Rect m_FrameSize;		// �ؽ����� �� �ϳ��� ����,����
		int m_FrameCount;		// m_MaxCellXCount * m_MaxCellYCount
		int m_MaxCellXCount;	// �ؽ����� x�� �� ����
		int m_MaxCellYCount;	// �ؽ����� y�� �� ����
		int m_MaxMapCellX;		// ��ü ���� x�� ����
		int m_MaxMapCellY;		// ��ü ���� y�� ����

		DISALLOW_COPY_AND_ASSIGN(TileMap);
		friend class Viewport;
	};
}
