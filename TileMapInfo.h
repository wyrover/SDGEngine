#pragma once

//----------------------------
//
//----------------------------
class CTileTemplateMgr;
class CImageObject;
class CTileMapInfo
{
public:
	CImageObject*		GetTileImageObject(int InX, int InY);

	int					GetTileId(int InX, int InY) const;

	void				CheckIsValidMapSize(int InX, int InY, int& OutX, int& OutY) const;

public:
	CTileTemplateMgr*	GetTileTemplate();
	void				SetTileTemplate(CTileTemplateMgr* InTileTemplate);

	const CRect&		GetOneTileSize();

	int					GetMaxMapCellX() const;
	void				SetMaxMapCellX(int InMaxMapCellX);

	int					GetMaxMapCellY() const;
	void				SetMaxMapCellY(int InMaxMapCellY);
public:
	CTileMapInfo(CTileTemplateMgr* InTileTemplateMgr, int InMaxMapCellX, int InMaxMapCellY);
	virtual ~CTileMapInfo();

public:
	CTileTemplateMgr*	m_TileTemplate;

	int					m_MaxMapCellX;
	int					m_MaxMapCellY;
};