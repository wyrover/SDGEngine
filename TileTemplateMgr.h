#pragma once

//#include "CImage.h"

//-------------------------------------------------------------
// class CTileMapMgr
//-------------------------------------------------------------
// 각 Tile 을 관리
// 1. Tile Template 을 Loading 하고 Tile( 텍스쳐 )을 생성
//
//-------------------------------------------------------------
class CImageInfo;
class CImageObject;
class CTileTemplateMgr
{
public:
	typedef std::vector< CImageObject* >		TypeTileList;
	typedef TypeTileList::iterator	TypeTileListIter;
public:
	BOOL	Create(LPDIRECT3DDEVICE9 pd3dDevice, const char* InTileTemplateFileName);
	BOOL	CreateTiles();

	CImageObject*	GetImageObject(int InImageId);

public:
	LPDIRECT3DDEVICE9	GetD3Device();
	void				SetD3Device(LPDIRECT3DDEVICE9 InD3Device);

	LPDIRECT3DTEXTURE9	GetTexture();
	void				SetTexture(LPDIRECT3DTEXTURE9 InTexture);

	CImageInfo*			GetImageInfo() const;

	int					GetFrameCount() const;
	void				SetFrameCount(int InFrameCount);

	int					GetMaxCellXCount() const;					// X 축 Cell 갯수
	void				SetMaxCellXCount(int InMaxCellXCount);	// X 축 Cell 갯수

	int					GetMaxCellYCount() const;					// Y 축 Cell 갯수
	void				SetMaxCellYCount(int MaxCellYCount);		// Y 축 Cell 갯수

	const CRect&		GetFrameSize() const;						// 각 Cell 사이즈
	void				SetFrameSize(const CRect& FrameSize);		// 각 Cell 사이즈

public:
	CTileTemplateMgr(const CRect& InFrameSize, int InFrameCount, int InMaxCellXCount, int InMaxCellYCount);
	virtual ~CTileTemplateMgr();

private:
	LPDIRECT3DDEVICE9	m_D3Device;

	TypeTileList		m_TileList;
	LPDIRECT3DTEXTURE9	m_TileTemplateImage;

	CImageInfo*			m_ImageInfo;

	CRect				m_FrameSize;
	int					m_FrameCount;
	int					m_MaxCellXCount;
	int					m_MaxCellYCount;
};

