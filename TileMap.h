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
		RECT m_FrameSize;		// �ؽ����� �� �ϳ��� ����,����
		int m_FrameCount;		// m_MaxCellXCount * m_MaxCellYCount
		int m_MaxCellXCount;	// �ؽ����� x�� �� ����
		int m_MaxCellYCount;	// �ؽ����� y�� �� ����
		int m_MaxMapCellX;		// ��ü ���� x�� ����
		int m_MaxMapCellY;		// ��ü ���� y�� ����

		friend class Viewport;
	};
}
