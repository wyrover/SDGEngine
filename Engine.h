#pragma once

namespace sidescroll
{
	class Engine : public MySingleton<Engine>
	{
	public:
		Engine();
		~Engine();

		int Run();
		LPDIRECT3DDEVICE9 Device()	const { return m_pd3dDevice; }
		lua_State *LuaState()		const { return m_lua; }
		HWND Handle()				const { return m_hwnd; }
		static LRESULT WINAPI MsgProc(HWND, UINT, WPARAM, LPARAM);

	private:
		HRESULT OnInit();
		void OnCleanUp();
		void OnRender();
		void OnUpdate(float delta);

		LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		LPDIRECT3D9 m_pD3D = nullptr;
		LPDIRECT3DDEVICE9 m_pd3dDevice = nullptr;
		HWND m_hwnd = nullptr;
		lua_State *m_lua = nullptr;
#ifdef _DEBUG
		FontAsset *m_FPS = nullptr;
#endif
		CTileTemplateMgr*		m_TileTempalte;
		CTileMapInfo*			m_TileMapInfo;
		CTileMapEngine*			m_TileEngine;

		D3DPRESENT_PARAMETERS m_d3dpp;
		DWORD m_dwStyle;
		std::string m_caption;
		std::string m_filepath;
		DWORD m_dwScreenWidth, m_dwScreenHeight;
	};
}