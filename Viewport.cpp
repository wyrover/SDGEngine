#include "Precompiled.h"

namespace SDGEngine
{
	Viewport::Viewport(TileMap *mapinfo, int ViewportW, int ViewportH)
		:m_TileMapInfo(mapinfo)
	{
		assert(ViewportW <= m_TileMapInfo->TotalMapX() && "뷰포트의 시야가 전체 맵보다 클 수는 없습니다!: X");
		assert(ViewportH <= m_TileMapInfo->TotalMapY() && "뷰포트의 시야가 전체 맵보다 클 수는 없습니다!: Y");

		m_ViewportX = ViewportW;
		m_ViewportY = ViewportH;

		m_ViewPort.SetRect(0, 0, m_TileMapInfo->GetOneTileSize().right * m_ViewportX,
			m_TileMapInfo->GetOneTileSize().bottom * m_ViewportY
			);
		m_TotalMapSize.SetRect(0, 0, m_TileMapInfo->GetOneTileSize().right * m_TileMapInfo->TotalMapX(),
			m_TileMapInfo->GetOneTileSize().bottom * m_TileMapInfo->TotalMapY()
			);
	}

	void Viewport::Update()
	{
		const float MoveUnit = 5.0f;

		if (Singleton<Input>::GetSingleton()->keyDown(DIK_D))
		{
			if ((m_ViewPort.left + MoveUnit) > m_TotalMapSize.right - m_ViewPort.right) {
				m_ViewPort.left = m_TotalMapSize.right - m_ViewPort.right;
			}
			else {
				m_ViewPort.left += MoveUnit;
			}
		}
		if (Singleton<Input>::GetSingleton()->keyDown(DIK_A))
		{
			if ((m_ViewPort.left - MoveUnit) < m_TotalMapSize.left) {
				m_ViewPort.left = m_TotalMapSize.left;
			}
			else {
				m_ViewPort.left -= MoveUnit;
			}
		}
		if (Singleton<Input>::GetSingleton()->keyDown(DIK_S))
		{
			if ((m_ViewPort.top + MoveUnit) > m_TotalMapSize.bottom - m_ViewPort.bottom) {
				m_ViewPort.top = m_TotalMapSize.bottom - m_ViewPort.bottom;
			}
			else {
				m_ViewPort.top += MoveUnit;
			}
		}
		if (Singleton<Input>::GetSingleton()->keyDown(DIK_W))
		{
			if ((m_ViewPort.top - MoveUnit) < m_TotalMapSize.top) {
				m_ViewPort.top = m_TotalMapSize.top;
			}
			else {
				m_ViewPort.top -= MoveUnit;
			}
		}

		RECT scissor;
		SetRect(&scissor, 0, 0, (int)m_ViewPort.right, (int)m_ViewPort.bottom);
		Singleton<Engine>::GetSingleton()->Device()->SetScissorRect(&scissor);
	}

	void Viewport::Render()
	{
		Rect onetile_size = m_TileMapInfo->GetOneTileSize();

		int FirstCellX = (int)(m_ViewPort.left / onetile_size.right);
		int FirstCellY = (int)(m_ViewPort.top / onetile_size.bottom);

		int EndCellX = FirstCellX + m_ViewportX;
		int EndCellY = FirstCellY + m_ViewportY;

		// 뷰포트 x,y
		int OffsetX = -(static_cast<int>(m_ViewPort.left) % static_cast<int>(onetile_size.right));
		int OffsetY = -(static_cast<int>(m_ViewPort.top) % static_cast<int>(onetile_size.bottom));

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
				Rect *tile_rect = m_TileMapInfo->GetTile(CurrCellX, CurrCellY);
				if (tile_rect)
				{
					Graphics::RenderQuad(
						m_TileMapInfo->m_TileTexture->width(),
						m_TileMapInfo->m_TileTexture->height(),
						D3DXVECTOR2(tile_rect->left, tile_rect->top),
						D3DXVECTOR2(onetile_size.right, onetile_size.bottom),
						D3DXVECTOR2(float(CurrPosX), float(CurrPosY))
						);
				}
				CurrPosX += (int)onetile_size.right;
			}
			CurrPosX = OffsetX;
			CurrPosY += (int)onetile_size.bottom;
		}
		Graphics::SetAlphatest(false);
		Graphics::BindTexture(NULL);
	}
}