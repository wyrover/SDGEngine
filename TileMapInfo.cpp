#include "Precompiled.h"

//--------------------------------------------
//
//--------------------------------------------
int CTileMapInfo::GetTileId(int InX, int InY) const
{
	int OutX = 0;
	int OutY = 0;

	CheckIsValidMapSize(InX, InY, OutX, OutY);

	//----------------------------------------
	// TestMap - 일단 가짜
	//----------------------------------------
	static const int TestTileMapId[10][10] =
	{
		{ 0, 1, 2, 3, 0, 0, 1, 2, 3, 1 },
		{ 1, 0, 3, 0, 2, 0, 1, 2, 3, 0 },
		{ 1, 6, 0, 7, 0, 0, 1, 2, 3, 0 },
		{ 0, 0, 0, 8, 0, 0, 1, 2, 3, 0 },
		{ 1, 0, 9, 0, 0, 0, 1, 2, 3, 0 },
		{ 0, 1, 2, 3, 0, 0, 1, 2, 3, 0 },
		{ 1, 0, 3, 0, 2, 0, 1, 2, 3, 0 },
		{ 1, 6, 0, 7, 0, 0, 1, 2, 3, 0 },
		{ 0, 0, 0, 8, 0, 0, 1, 2, 3, 0 },
		{ 1, 0, 9, 0, 0, 0, 1, 2, 3, 0 },
	};

	return TestTileMapId[OutY][OutX];
}
//--------------------------------------------
//
//--------------------------------------------
void CTileMapInfo::CheckIsValidMapSize(int InX, int InY, int& OutX, int& OutY) const
{
	int TempMapCellX = InX;
	int TempMapCellY = InY;

	if (TempMapCellX < 0)
	{
		TempMapCellX = 0;
	}

	if (TempMapCellX > GetMaxMapCellX() - 1)
	{
		TempMapCellX = GetMaxMapCellX() - 1;
	}

	if (TempMapCellY < 0)
	{
		TempMapCellY = 0;
	}

	if (TempMapCellY > GetMaxMapCellY() - 1)
	{
		TempMapCellY = GetMaxMapCellY() - 1;
	}

	OutX = TempMapCellX;
	OutY = TempMapCellY;
}

//--------------------------------------------
//
//--------------------------------------------
CImageObject* CTileMapInfo::GetTileImageObject(int InX, int InY)
{
	int TempTileImageId = GetTileId(InX, InY);

	CImageObject* TempImageObject = GetTileTemplate()->GetImageObject(TempTileImageId);

	return TempImageObject;
}
//--------------------------------------------
//
//--------------------------------------------
CTileTemplateMgr* CTileMapInfo::GetTileTemplate()
{
	return m_TileTemplate;
}
//--------------------------------------------
//
//--------------------------------------------
void CTileMapInfo::SetTileTemplate(CTileTemplateMgr* InTileTemplate)
{
	m_TileTemplate = InTileTemplate;
}
//--------------------------------------------
//
//--------------------------------------------
const CRect& CTileMapInfo::GetOneTileSize()
{
	return GetTileTemplate()->GetFrameSize();
}
//--------------------------------------------
//
//--------------------------------------------
int	CTileMapInfo::GetMaxMapCellX() const
{
	return m_MaxMapCellX;
}
//--------------------------------------------
//
//--------------------------------------------
void CTileMapInfo::SetMaxMapCellX(int InMaxMapCellX)
{
	m_MaxMapCellX = InMaxMapCellX;
}
//--------------------------------------------
//
//--------------------------------------------
int	CTileMapInfo::GetMaxMapCellY() const
{
	return m_MaxMapCellY;
}
//--------------------------------------------
//
//--------------------------------------------
void CTileMapInfo::SetMaxMapCellY(int InMaxMapCellY)
{
	m_MaxMapCellY = InMaxMapCellY;
}
//--------------------------------------------
//
//--------------------------------------------
CTileMapInfo::CTileMapInfo(CTileTemplateMgr* InTileTemplateMgr, int InMaxMapCellX, int InMaxMapCellY)
{
	SetTileTemplate(InTileTemplateMgr);
	SetMaxMapCellX(InMaxMapCellX);
	SetMaxMapCellY(InMaxMapCellY);
}

//--------------------------------------------
//
//--------------------------------------------
CTileMapInfo::~CTileMapInfo()
{
	;
}