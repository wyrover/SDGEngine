#include "Precompiled.h"

namespace SDGEngine
{
	TileMap::TileMap(const std::string &path, const float width, const float height, int InMaxMapCellX, int InMaxMapCellY)
	{
		m_FrameSize.SetRect(0, 0, width, height);
		m_TileTexture = Singleton<Assets>::GetSingleton()->RequestTexture(path);
		assert(m_TileTexture);
		m_MaxCellXCount = static_cast<int>(m_TileTexture->width() / width);
		m_MaxCellYCount = static_cast<int>(m_TileTexture->height() / height);
		m_MaxMapCellX = InMaxMapCellX;
		m_MaxMapCellY = InMaxMapCellY;
		m_FrameCount = m_MaxCellXCount * m_MaxCellYCount;
		CreateTiles();
	}

	TileMap::~TileMap()
	{
		for (auto i : m_TileSet)
		{
			SDELETE(i);
		}
		m_TileTexture->RemoveReference();
	}

	void TileMap::CreateTiles()
	{
		Rect TempTagetRect;

		for (int CurrFrame = 0; CurrFrame < m_FrameCount; ++CurrFrame)
		{
			GetCellPos(CurrFrame, &TempTagetRect);

			Rect *tempRect = new Rect;
			tempRect->SetRect(TempTagetRect.left, TempTagetRect.top, TempTagetRect.right, TempTagetRect.bottom);
			m_TileSet.push_back(tempRect);
		}
	}

	void TileMap::GetCellPos(const int InFrameNumber, Rect *OutTargetRect)
	{
		int TempCellX = 0;
		int TempCellY = 0;

		if (m_MaxCellXCount > 0)
		{
			TempCellX = InFrameNumber % m_MaxCellXCount;
			TempCellY = (InFrameNumber) / m_MaxCellXCount;
		}

		float TargetX = TempCellX * m_FrameSize.right;
		float TargetY = TempCellY * m_FrameSize.bottom;

		OutTargetRect->SetRect(TargetX, TargetY, static_cast<float>(TargetX + m_FrameSize.right), static_cast<float>(TargetY + m_FrameSize.bottom));
	}

	Rect *TileMap::GetCellRect(unsigned int cellid)
	{
		if (cellid < m_TileSet.size())
		{
			return m_TileSet[cellid];
		}

		return NULL;
	}

	int TileMap::GetTileId(int InX, int InY) const
	{
		int OutX = 0;
		int OutY = 0;

		CheckIsValidMapSize(InX, InY, OutX, OutY);

		// y, x
		static const int TestTileMapId[25][32] = {
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 37, 0, 39, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45, 46, 47, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 61, 62, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 69, 70, 71, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 77, 78, 79, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 85, 86, 87, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 93, 94, 95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 101, 102, 103, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 109, 110, 111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 1, 1 }
		};

		return TestTileMapId[OutY][OutX];
	}

	void TileMap::CheckIsValidMapSize(int InX, int InY, int& OutX, int& OutY) const
	{
		int TempMapCellX = InX;
		int TempMapCellY = InY;

		if (TempMapCellX < 0)
		{
			TempMapCellX = 0;
		}

		if (TempMapCellX > m_MaxMapCellX - 1)
		{
			TempMapCellX = m_MaxMapCellX - 1;
		}

		if (TempMapCellY < 0)
		{
			TempMapCellY = 0;
		}

		if (TempMapCellY > m_MaxMapCellY - 1)
		{
			TempMapCellY = m_MaxMapCellY - 1;
		}

		OutX = TempMapCellX;
		OutY = TempMapCellY;
	}

	Rect *TileMap::GetTile(int InX, int InY)
	{
		return GetCellRect(GetTileId(InX, InY));
	}
}
