#pragma once

//#include "CImage.h"

//-------------------------------------------------------------
// class CTileMapMgr
//-------------------------------------------------------------
// �� Tile �� ����
// 1. Tile Template �� Loading �ϰ� Tile( �ؽ��� )�� ����
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

	int					GetMaxCellXCount() const;					// X �� Cell ����
	void				SetMaxCellXCount(int InMaxCellXCount);	// X �� Cell ����

	int					GetMaxCellYCount() const;					// Y �� Cell ����
	void				SetMaxCellYCount(int MaxCellYCount);		// Y �� Cell ����

	const CRect&		GetFrameSize() const;						// �� Cell ������
	void				SetFrameSize(const CRect& FrameSize);		// �� Cell ������

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

