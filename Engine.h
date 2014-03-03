#pragma once

namespace sidescroll
{
	class Engine;
	extern Engine* ENGINE;
	class Engine
	{
	public:
		Engine(HINSTANCE inst);
		~Engine();

		int Run();
		LPDIRECT3DDEVICE9 device()	const { return m_pd3dDevice; }
		lua_State *LuaState()		const { return m_lua; }
		HWND Handle()				const { return m_hwnd; }
		HINSTANCE instance()		const { return m_hInst; }
		static  LRESULT WINAPI MsgProc(HWND, UINT, WPARAM, LPARAM);

	private:
		HRESULT OnInit();
		void OnCleanUp();
		void OnRender();
		void OnUpdate(float delta);

		void ParseEngineiniFile();
		LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		LPDIRECT3D9 m_pD3D = nullptr;
		LPDIRECT3DDEVICE9 m_pd3dDevice = nullptr;
		HWND m_hwnd = nullptr;
		HINSTANCE m_hInst = nullptr;
		lua_State *m_lua = nullptr;
		Time *time = nullptr;
		Input *input = nullptr;
		SceneQueue *m_sceneQueue = nullptr;
		Assets *m_assets = nullptr;
		Debug *m_debug = nullptr;
		FontAsset *FPS = nullptr;
		D3DPRESENT_PARAMETERS d3dpp;
		DWORD m_dwStyle;
		std::string m_caption;
		DWORD m_dwScreenWidth, m_dwScreenHeight;
	};
}