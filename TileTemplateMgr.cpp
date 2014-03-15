#include "Precompiled.h"

//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
BOOL CTileTemplateMgr::Create(LPDIRECT3DDEVICE9 pd3dDevice, const char* InTileTemplateFileName)
{
	if (!pd3dDevice)
	{
		return FALSE;
	}

	SetD3Device(pd3dDevice);
	//-----------------------------------------------------------------
	//	�ش� Texture File�� Loading �Ѵ�
	//-----------------------------------------------------------------
	if (!(m_ImageInfo = new CImageInfo(InTileTemplateFileName)))
	{
		return FALSE;
	}

	D3DCOLOR transparencycolor;
	transparencycolor = D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00);		//����� ���

	//-----------------------------------------------------------------
	//	�ش� Texture File�� Loading �Ѵ�
	//-----------------------------------------------------------------
	if (FAILED(D3DXCreateTextureFromFileEx(GetD3Device(), InTileTemplateFileName,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_TRIANGLE | D3DX_FILTER_MIRROR,
		D3DX_FILTER_TRIANGLE | D3DX_FILTER_MIRROR,
		transparencycolor,
		NULL, NULL,
		&m_TileTemplateImage)))
	{
		return FALSE;
	}

	//------------------------------------------------------------
	// Ÿ���� ����
	//------------------------------------------------------------
	CreateTiles();

	return TRUE;
}

//-------------------------------------------------------------
//
//-------------------------------------------------------------
bool GetImageCellPos(const int InMaxCellX, const int InMaxCellY, const int InFrameNumber, const CRect& InFrameSize, CRect& OutTargetRect)
{
	//-------------------------------------------------------------
	//
	//-------------------------------------------------------------
	int TempCellX = 0;
	int TempCellY = 0;

	if (InMaxCellX > 0)
	{
		TempCellX = InFrameNumber % InMaxCellX;
		TempCellY = (InFrameNumber) / InMaxCellX;
	}

	int TargetX = TempCellX * static_cast<int>(InFrameSize.Width());
	int TargetY = TempCellY * static_cast<int>(InFrameSize.Height());

	OutTargetRect = CRect(TargetX, TargetY, TargetX + InFrameSize.Width(), TargetY + InFrameSize.Height());

	return true;
}

//-------------------------------------------------------------------
// �� �� ������ ��ü�� ����
//-------------------------------------------------------------------
BOOL CTileTemplateMgr::CreateTiles()
{
	const int	MaxImageCount = GetFrameCount();		// ��ü Cell ����
	const int	MaxCellXCount = GetMaxCellXCount();	// X �� Cell ����
	const int	MaxCellYCount = GetMaxCellYCount();	// Y �� Cell ����
	CRect		FrameSize = GetFrameSize();		// �� Cell ������

	for (int CurrFrame = 0; CurrFrame < MaxImageCount; ++CurrFrame)
	{
		//-----------------------------------
		// 1. UV ��ǥ ���
		//-----------------------------------
		CRect TempTagetRect;
		GetImageCellPos(MaxCellXCount, MaxCellYCount, CurrFrame, FrameSize, TempTagetRect);

		CRect TempTemplateImageSize = GetImageInfo()->GetImageSize();
		CRect TempTexUV;

		TempTexUV.SetLeft(TempTagetRect.Left() / TempTemplateImageSize.Width());
		TempTexUV.SetRight(TempTagetRect.Right() / TempTemplateImageSize.Width());
		TempTexUV.SetTop(TempTagetRect.Top() / TempTemplateImageSize.Height());
		TempTexUV.SetBottom(TempTagetRect.Bottom() / TempTemplateImageSize.Height());
		//----------------------------------
		// 2. CImageObject ��ü ����
		//----------------------------------
		CImageObject* TempImageObject = new CImageObject(GetD3Device(), GetTexture(), FrameSize, TempTexUV);

		m_TileList.push_back(TempImageObject);
	}
	return TRUE;
}
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
CImageObject* CTileTemplateMgr::GetImageObject(int InImageId)
{
	if (InImageId < m_TileList.size())
	{
		return m_TileList[InImageId];
	}
	return NULL;
}
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
LPDIRECT3DDEVICE9 CTileTemplateMgr::GetD3Device()
{
	return m_D3Device;
}
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
void CTileTemplateMgr::SetD3Device(LPDIRECT3DDEVICE9 InD3Device)
{
	m_D3Device = InD3Device;
}
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CTileTemplateMgr::GetTexture()
{
	return m_TileTemplateImage;
}
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
CImageInfo*	CTileTemplateMgr::GetImageInfo() const
{
	return m_ImageInfo;
}
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
void CTileTemplateMgr::SetTexture(LPDIRECT3DTEXTURE9 InTexture)
{
	m_TileTemplateImage = InTexture;
}
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
int	CTileTemplateMgr::GetFrameCount() const
{
	return m_FrameCount;
}
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
void CTileTemplateMgr::SetFrameCount(int InFrameCount)
{
	m_FrameCount = InFrameCount;
}
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
int	CTileTemplateMgr::GetMaxCellXCount() const
{
	return m_MaxCellXCount;
}
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
void CTileTemplateMgr::SetMaxCellXCount(int InMaxCellXCount)
{
	m_MaxCellXCount = InMaxCellXCount;
}
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
int CTileTemplateMgr::GetMaxCellYCount() const
{
	return m_MaxCellYCount;
}
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
void CTileTemplateMgr::SetMaxCellYCount(int MaxCellYCount)
{
	m_MaxCellYCount = MaxCellYCount;
}
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
const CRect& CTileTemplateMgr::GetFrameSize() const
{
	return m_FrameSize;
}
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
void CTileTemplateMgr::SetFrameSize(const CRect& FrameSize)		// �� Cell ������
{
	m_FrameSize = FrameSize;
}
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
CTileTemplateMgr::CTileTemplateMgr(const CRect& InFrameSize, int InFrameCount, int InMaxCellXCount, int InMaxCellYCount)
{
	SetFrameSize(InFrameSize);
	SetFrameCount(InFrameCount);
	SetMaxCellXCount(InMaxCellXCount);
	SetMaxCellYCount(InMaxCellYCount);

	m_TileList.reserve(100);

	m_TileTemplateImage = NULL;
	m_ImageInfo = NULL;
}
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
CTileTemplateMgr::~CTileTemplateMgr()
{
	SAFE_RELEASE(m_TileTemplateImage);
}