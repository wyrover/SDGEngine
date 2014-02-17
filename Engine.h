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

	void addSceneFromQueue(GameScene *scene);
	void removeSceneFromQueue();
	void removeAllSceneFromQueue();
	void deleteAllFromRemovedQueue();
	size_t getSceneQueueSize() { return m_SceneQueue.size(); }

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
	HINSTANCE m_hInst = nullptr;
	lua_State *m_lua = nullptr;
	Font *frameRateFont;
	Time *time = nullptr;
	Input *input = nullptr;
	D3DPRESENT_PARAMETERS d3dpp;
	DWORD m_dwStyle;
	std::string m_caption;
	DWORD m_dwScreenWidth, m_dwScreenHeight;
	std::queue<GameScene *> m_SceneQueue;
	std::queue<GameScene *> m_RemovedSceneQueue;
};