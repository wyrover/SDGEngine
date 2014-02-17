#pragma once

class Engine;
extern Engine* ENGINE;
class Engine
{
public:
	Engine(HINSTANCE inst);
	~Engine();

	int Run();
	LPDIRECT3DDEVICE9 device() { return m_pd3dDevice; }
	lua_State *LuaState() { return m_lua; }
	HWND Handle() { return m_hwnd; }
	HINSTANCE instance() { return m_hInst; }
	static  LRESULT WINAPI MsgProc(HWND, UINT, WPARAM, LPARAM);

private:
	HRESULT OnInit();
	void OnCleanUp();
	void OnRender();
	void OnUpdate(float delta);

	LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	LPDIRECT3D9 m_pD3D = nullptr;
	LPDIRECT3DDEVICE9 m_pd3dDevice = nullptr;
	D3DPRESENT_PARAMETERS d3dpp;
	HWND m_hwnd = nullptr;
	HINSTANCE m_hInst = nullptr;
	DWORD m_dwStyle;
	std::string m_caption;
	DWORD m_dwScreenWidth, m_dwScreenHeight;
	lua_State *m_lua = nullptr;
	Font *frameRateFont;
	Time *time = nullptr;
	Input *input = nullptr;
	Space space;
};