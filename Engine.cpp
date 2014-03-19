#include "Precompiled.h"

namespace SDGEngine
{
	Engine::Engine()
	{
		m_dwStyle = WS_CAPTION | WS_SYSMENU;
		m_caption = "SDGEngine";
		m_filepath = "test.lua";
		m_dwScreenWidth = 1024;
		m_dwScreenHeight = 800;
	}

	Engine::~Engine()
	{
		lua_close(m_lua);
	}

	HRESULT Engine::OnInit()
	{
		Lua::DefaultRegistration();
		m_lua = Lua::CreateEnvironment(m_filepath);

		WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
			GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
			m_caption.c_str(), NULL };
		RegisterClassEx(&wc);

		RECT rt = { 0, 0, m_dwScreenWidth, m_dwScreenHeight };
		AdjustWindowRect(&rt, m_dwStyle, false);

		DWORD width = rt.right - rt.left;
		DWORD height = rt.bottom - rt.top;
		unsigned m_uiClientPosX = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2;
		unsigned m_uiClientPosY = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;

		m_hwnd = CreateWindow(m_caption.c_str(), m_caption.c_str(),
			m_dwStyle, m_uiClientPosX, m_uiClientPosY, m_dwScreenWidth, m_dwScreenHeight,
			GetDesktopWindow(), NULL, g_hInstance, NULL);
		if (!m_hwnd)
			return E_FAIL;

		if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
			return E_FAIL;

		ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));
		m_d3dpp.Windowed = TRUE;
		m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		m_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hwnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_d3dpp, &m_pd3dDevice)))
			return E_FAIL;

		if (FAILED(m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE)))
			return E_FAIL;

		if (FAILED(m_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE)))
			return E_FAIL;

		if (!Singleton<Time>::GetSingleton()->Init())
			return E_FAIL;

		if (!Singleton<Input>::GetSingleton()->Init())
			return E_FAIL;

		if (!Singleton<FmodAudioSystem>::GetSingleton()->Init())
			return E_FAIL;

		Singleton<SceneSystem>::GetSingleton()->Init();
		Singleton<SceneSystem>::GetSingleton()->ChangeScene(new LogoScene);
#ifdef _DEBUG
		m_FPS = Singleton<Assets>::GetSingleton()->RequestFont("Arial", 14);
#endif
		return S_OK;
	}

	void Engine::OnCleanUp()
	{
#ifdef _DEBUG
		m_FPS->RemoveReference();
#endif
		SRELEASE(m_pd3dDevice);
		SRELEASE(m_pD3D);
	}

	void Engine::OnRender()
	{
		if (NULL == m_pd3dDevice)
			return;

		m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, Colours::White, 1.0f, 0);
		if (SUCCEEDED(m_pd3dDevice->BeginScene()))
		{
			Singleton<Viewport>::GetSingleton()->Render();
			Singleton<SceneSystem>::GetSingleton()->Render();
#ifdef DEBUG
			Graphics::RenderText(*m_FPS, 10, 10, "frameRate: %ld", Singleton<Time>::GetSingleton()->frameRate());
#endif
			m_pd3dDevice->EndScene();
		}

		m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
	}

	void Engine::OnUpdate(float delta)
	{
		Singleton<Viewport>::GetSingleton()->Update(delta);
		Singleton<SceneSystem>::GetSingleton()->Update(delta);
	}

	int Engine::Run()
	{
		if (FAILED(OnInit()))
			return 0;

		ShowWindow(m_hwnd, SW_SHOWDEFAULT);
		UpdateWindow(m_hwnd);

		MSG msg = { 0, };
		while (msg.message != WM_QUIT)
		{
			if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
			else
			{
				Singleton<Time>::GetSingleton()->Start();
				Singleton<Input>::GetSingleton()->Capture();
				Singleton<FmodAudioSystem>::GetSingleton()->AudioSystem()->update();
				OnUpdate(Singleton<Time>::GetSingleton()->deltaTime());
				OnRender();
			}
		}

		UnregisterClass(m_caption.c_str(), g_hInstance);

		return 0;
	}

	LRESULT Engine::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
#ifdef _DEBUG
		case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_ESCAPE:
				PostMessage(Handle(), WM_DESTROY, NULL, NULL);
				return 0;
			}
			break;
#endif
		case WM_IME_STARTCOMPOSITION:
			return 0;
		case WM_DESTROY:
			OnCleanUp();
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	LRESULT WINAPI Engine::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return Singleton<Engine>::GetSingleton()->WndProc(hWnd, msg, wParam, lParam);
	}
}
