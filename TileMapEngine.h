#pragma once

class CTileMapInfo;
class CTileMapEngine
{
public:
	void	Create(LPDIRECT3DDEVICE9 InD3dDevice, const CRect& InViewPort);
	BOOL	Update();

	void	ProcessKeyInput();
	void	Draw();

public:
	CTileMapInfo*	GetTileMapInfo();
	void			SetTileMapInfo(CTileMapInfo* InTileMapInfo);

	LPDIRECT3DDEVICE9	GetD3dDevice();
	void				SetD3dDevice(LPDIRECT3DDEVICE9 InD3dDevice);

	const CRect&		GetViewPort() const;
	void				SetViewPort(const CRect& InViewPort);

public:
	CTileMapEngine(LPDIRECT3DDEVICE9 InD3dDevice, const CRect& InViewPort);
	virtual ~CTileMapEngine();

private:
	LPDIRECT3DDEVICE9	m_D3dDevice;
	CRect				m_ViewPort;

	CTileMapInfo*		m_TileMapInfo;
};