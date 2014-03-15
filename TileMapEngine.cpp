#include "Precompiled.h"

//-----------------------------------------------
//
//-----------------------------------------------
void CTileMapEngine::Create(LPDIRECT3DDEVICE9 InD3dDevice, const CRect& InViewPort)
{
	SetD3dDevice(InD3dDevice);
	SetViewPort(InViewPort);
}
//-----------------------------------------------
//
//-----------------------------------------------
BOOL CTileMapEngine::Update()
{
	ProcessKeyInput();
	Draw();

	return TRUE;
}

//-----------------------------------------------
//
//-----------------------------------------------
void CTileMapEngine::ProcessKeyInput()
{
	const float MoveUnit = 0.1f;

	float TempViewPortLeft = GetViewPort().Left();
	float TempViewPortTop = GetViewPort().Top();
	float TempViewPortWidth = GetViewPort().Width();
	float TempViewPortHeight = GetViewPort().Height();

	CRect TotalMapSize(0, 0, 65 * 10, 65 * 10);

	if (KEY_DOWN(VK_RIGHT))
	{
		if ((TempViewPortLeft += MoveUnit) > TotalMapSize.Right() - TempViewPortWidth)
		{
			TempViewPortLeft = TotalMapSize.Right() - TempViewPortWidth;
		}
	}
	if (KEY_DOWN(VK_LEFT))
	{
		if ((TempViewPortLeft -= MoveUnit) < TotalMapSize.Left())
		{
			TempViewPortLeft = TotalMapSize.Left();
		}
	}
	if (KEY_DOWN(VK_DOWN))
	{
		if ((TempViewPortTop += MoveUnit) > TotalMapSize.Bottom() - TempViewPortHeight)
		{
			TempViewPortTop = TotalMapSize.Bottom() - TempViewPortHeight;
		}
	}
	if (KEY_DOWN(VK_UP))
	{
		if ((TempViewPortTop -= MoveUnit) < TotalMapSize.Top())
		{
			TempViewPortTop = TotalMapSize.Top();
		}
	}

	SetViewPort(CRect(TempViewPortLeft,
		TempViewPortTop,
		TempViewPortLeft + TempViewPortWidth,
		TempViewPortTop + TempViewPortHeight));
}

//-----------------------------------------------
//
//-----------------------------------------------
void CTileMapEngine::Draw()
{
	//----------------------------------------------
	//
	//----------------------------------------------
	CScissorTestMgr TempScissorTest(GetD3dDevice(), CRect(0, 0, GetViewPort().Width(), GetViewPort().Height()));


	//-----------------------------
	//
	//-----------------------------
	CRect TileSize = GetTileMapInfo()->GetOneTileSize();
	CRect CurViewPort = GetViewPort();

	int FirstCellX = CurViewPort.Left() / TileSize.Width();
	int FirstCellY = CurViewPort.Top() / TileSize.Height();

	int EndCellX = FirstCellX + 5;
	int EndCellY = FirstCellY + 5;

	int	OffsetX = -(static_cast<int>(CurViewPort.Left()) % static_cast<int>(TileSize.Width()));
	int OffsetY = -(static_cast<int>(CurViewPort.Top()) % static_cast<int>(TileSize.Height()));

	int CurrPosX = OffsetX;
	int CurrPosY = OffsetY;

	if (OffsetX)
	{
		++EndCellX;
	}

	if (OffsetY)
	{
		++EndCellY;
	}

	for (int CurrCellY = FirstCellY; CurrCellY < EndCellY; ++CurrCellY)
	{
		for (int CurrCellX = FirstCellX; CurrCellX < EndCellX; ++CurrCellX)
		{
			CImageObject* TempImageObject = GetTileMapInfo()->GetTileImageObject(CurrCellX, CurrCellY);
			if (TempImageObject)
			{
				TempImageObject->Draw(CurrPosX, CurrPosY);
			}
			CurrPosX += TileSize.Width();
		}
		CurrPosX = OffsetX;
		CurrPosY += TileSize.Height();
	}
}

//-----------------------------------------------
//
//-----------------------------------------------
CTileMapInfo* CTileMapEngine::GetTileMapInfo()
{
	return m_TileMapInfo;
}
//-----------------------------------------------
//
//-----------------------------------------------
void CTileMapEngine::SetTileMapInfo(CTileMapInfo* InTileMapInfo)
{
	m_TileMapInfo = InTileMapInfo;
}
//-----------------------------------------------
//
//-----------------------------------------------
LPDIRECT3DDEVICE9 CTileMapEngine::GetD3dDevice()
{
	return m_D3dDevice;
}
//-----------------------------------------------
//
//-----------------------------------------------
void CTileMapEngine::SetD3dDevice(LPDIRECT3DDEVICE9 InD3dDevice)
{
	m_D3dDevice = InD3dDevice;
}

//-----------------------------------------------
//
//-----------------------------------------------
const CRect& CTileMapEngine::GetViewPort() const
{
	return m_ViewPort;
}
//-----------------------------------------------
//
//-----------------------------------------------
void CTileMapEngine::SetViewPort(const CRect& InViewPort)
{
	m_ViewPort = InViewPort;
}


//-----------------------------------------------
//
//-----------------------------------------------
CTileMapEngine::CTileMapEngine(LPDIRECT3DDEVICE9 InD3dDevice, const CRect& InViewPort)
{
	Create(InD3dDevice, InViewPort);
}
//-----------------------------------------------
//
//-----------------------------------------------
CTileMapEngine::~CTileMapEngine()
{

}