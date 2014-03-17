#include "Precompiled.h"

namespace SDGEngine
{
	TileMap::TileMap(const std::string &path, const int width, const int height, int InMaxMapCellX, int InMaxMapCellY)
	{
		SetRect(&m_FrameSize, 0, 0, width, height);
		m_TileTexture = Singleton<Assets>::GetSingleton()->RequestTexture(path);
		assert(m_TileTexture);
		m_MaxCellXCount = m_TileTexture->width() / width;
		m_MaxCellYCount = m_TileTexture->height() / height;
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

	bool TileMap::CreateTiles()
	{
		RECT TempTagetRect;
		int retval = false;

		for (int CurrFrame = 0; CurrFrame < m_FrameCount; ++CurrFrame)
		{
			GetCellPos(CurrFrame, &TempTagetRect);

			RECT *tempRect = new RECT;
			retval = SetRect(tempRect, TempTagetRect.left, TempTagetRect.top, TempTagetRect.right, TempTagetRect.bottom);
			if (!retval) return false;
			m_TileSet.push_back(tempRect);
		}

		return true;
	}

	bool TileMap::GetCellPos(const int InFrameNumber, RECT *OutTargetRect)
	{
		int TempCellX = 0;
		int TempCellY = 0;

		if (m_MaxCellXCount > 0)
		{
			TempCellX = InFrameNumber % m_MaxCellXCount;
			TempCellY = (InFrameNumber) / m_MaxCellXCount;
		}

		int TargetX = TempCellX * static_cast<int>(m_FrameSize.right);
		int TargetY = TempCellY * static_cast<int>(m_FrameSize.bottom);

		int retval = SetRect(OutTargetRect, TargetX, TargetY, TargetX + m_FrameSize.right, TargetY + m_FrameSize.bottom);
		if (!retval) return false;

		return true;
	}

	RECT* TileMap::GetCellRect(unsigned int cellid)
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

		static const int TestTileMapId[10][10] =
		{
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 4, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 4, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 4, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
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

	RECT *TileMap::GetTile(int InX, int InY)
	{
		return GetCellRect(GetTileId(InX, InY));
	}
}
