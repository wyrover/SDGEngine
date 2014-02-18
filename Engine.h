#pragma once

class Engine;
extern Engine* ENGINE;
class Engine
{
public:
	Engine(HINSTANCE inst);
	~Engine();

	int Run();
	LPDIRECT3DDEVICE9 device()	const { return m_pd3dDevice; }
	lua_State *LuaState()		const { return m_lua;	}
	HWND Handle()				const { return m_hwnd;	}
	HINSTANCE instance()		const { return m_hInst; }
	Time *TIME()				const { return time;	}
	Input *INPUT()				const { return input;	}
	static  LRESULT WINAPI MsgProc(HWND, UINT, WPARAM, LPARAM);

	void addFromSceneQueue(GameScene *scene);
	void removeFromSceneQueue();
	void removeAllFromSceneQueue();
	void deleteAllFromRemovedQueue();
	size_t getSceneQueueSize() { return m_SceneQueue.size(); }

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