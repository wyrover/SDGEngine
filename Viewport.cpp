#include "Precompiled.h"

namespace sidescroll
{
	Viewport::Viewport(TileMap *mapinfo, const int ViewportW, const int ViewportH)
	{
		SetRect(&m_ViewPort, 0, 0, ViewportW, ViewportH);
		m_TileMapInfo = mapinfo;
	}

	void Viewport::Update()
	{
		const float MoveUnit = 1.0f;

		float TempViewPortLeft = m_ViewPort.left;
		float TempViewPortTop = m_ViewPort.top;
		float TempViewPortWidth = m_ViewPort.right;
		float TempViewPortHeight = m_ViewPort.bottom;

		RECT TotalMapSize;
		SetRect(&TotalMapSize, 0, 0, 65 * 10, 65 * 10); // ¿ä°Å ¹Ù²Ü°Í 10

		if (Singleton<Input>::GetSingleton()->keyDown(DIK_RIGHT))
		{
			if ((TempViewPortLeft += MoveUnit) > TotalMapSize.right - TempViewPortWidth)
			{
				TempViewPortLeft = TotalMapSize.right - TempViewPortWidth;
			}
		}
		if (Singleton<Input>::GetSingleton()->keyDown(DIK_LEFT))
		{
			if ((TempViewPortLeft -= MoveUnit) < TotalMapSize.left)
			{
				TempViewPortLeft = TotalMapSize.left;
			}
		}
		if (Singleton<Input>::GetSingleton()->keyDown(DIK_DOWN))
		{
			if ((TempViewPortTop += MoveUnit) > TotalMapSize.bottom - TempViewPortHeight)
			{
				TempViewPortTop = TotalMapSize.bottom - TempViewPortHeight;
			}
		}
		if (Singleton<Input>::GetSingleton()->keyDown(DIK_UP))
		{
			if ((TempViewPortTop -= MoveUnit) < TotalMapSize.top)
			{
				TempViewPortTop = TotalMapSize.top;
			}
		}

		SetRect(&m_ViewPort, TempViewPortLeft,
			TempViewPortTop,
			TempViewPortLeft + TempViewPortWidth,
			TempViewPortTop + TempViewPortHeight
			);
	}

	void Viewport::Render()
	{
		const RECT *TileSize = m_TileMapInfo->GetOneTileSize();

		int FirstCellX = m_ViewPort.left / TileSize->right;
		int FirstCellY = m_ViewPort.top / TileSize->bottom;

		// ¿ä°Å ¹Ù²Ü°Í 5
		int EndCellX = FirstCellX + 5;
		int EndCellY = FirstCellY + 5;

		// ºäÆ÷Æ® x,y
		int	OffsetX = -(static_cast<int>(m_ViewPort.left) % static_cast<int>(TileSize->right));
		int OffsetY = -(static_cast<int>(m_ViewPort.top) % static_cast<int>(TileSize->bottom));

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

		Graphics::SetAlphatest(true);
		Graphics::BindTexture(m_TileMapInfo->m_TileTexture);
		for (int CurrCellY = FirstCellY; CurrCellY < EndCellY; ++CurrCellY)
		{
			for (int CurrCellX = FirstCellX; CurrCellX < EndCellX; ++CurrCellX)
			{
				RECT* TempImageObject = m_TileMapInfo->GetTile(CurrCellX, CurrCellY);
				if (TempImageObject)
				{
					Graphics::RenderQuad(
						m_TileMapInfo->m_TileTexture->width(),
						m_TileMapInfo->m_TileTexture->height(),
						D3DXVECTOR2(TempImageObject->left, TempImageObject->top),
						D3DXVECTOR2(TempImageObject->right * 2, TempImageObject->bottom * 2),
						D3DXVECTOR2(CurrPosX, CurrPosY)
						);
				}
				CurrPosX += TileSize->right;
			}
			CurrPosX = OffsetX;
			CurrPosY += TileSize->bottom;
		}
		Graphics::SetAlphatest(false);
		Graphics::BindTexture(nullptr);
	}
}