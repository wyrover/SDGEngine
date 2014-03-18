#pragma once

namespace SDGEngine
{
	class Engine : public Singleton<Engine>
	{
	public:
		Engine();
		virtual ~Engine();

		int						Run();
		LPDIRECT3DDEVICE9		Device()		const { return m_pd3dDevice; }
		lua_State				*LuaState()		const { return m_lua;		 }
		HWND					Handle()		const { return m_hwnd;		 }
		FontAsset				*GetFont()		const { return m_FPS;		 }	
		static LRESULT WINAPI	MsgProc(HWND, UINT, WPARAM, LPARAM);

	private:
		HRESULT					OnInit();
		void					OnCleanUp();
		void					OnRender();
		void					OnUpdate(float delta);

		LRESULT					WndProc(HWND, UINT, WPARAM, LPARAM);

	private:
		LPDIRECT3D9				m_pD3D			= NULL;
		LPDIRECT3DDEVICE9		m_pd3dDevice	= NULL;
		HWND					m_hwnd			= NULL;
		lua_State				*m_lua			= NULL;
#ifdef _DEBUG
		FontAsset				*m_FPS			= NULL;
#endif
		D3DPRESENT_PARAMETERS	m_d3dpp;
		DWORD					m_dwStyle;
		std::string				m_caption;
		std::string				m_filepath;
		DWORD					m_dwScreenWidth;
		DWORD					m_dwScreenHeight;
		DISALLOW_COPY_AND_ASSIGN(Engine);
	};
}