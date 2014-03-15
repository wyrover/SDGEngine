#include "Precompiled.h"

namespace sidescroll
{
	Engine::Engine()
	{
		m_dwStyle = WS_CAPTION | WS_SYSMENU;
		m_caption = "Test application";
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
			GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr,
			m_caption.c_str(), nullptr };
		RegisterClassEx(&wc);

		RECT rt = { 0, 0, m_dwScreenWidth, m_dwScreenHeight };
		AdjustWindowRect(&rt, m_dwStyle, false);

		DWORD width = rt.right - rt.left;
		DWORD height = rt.bottom - rt.top;
		unsigned m_uiClientPosX = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2;
		unsigned m_uiClientPosY = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;

		m_hwnd = CreateWindow(m_caption.c_str(), m_caption.c_str(),
			m_dwStyle, m_uiClientPosX, m_uiClientPosY, m_dwScreenWidth, m_dwScreenHeight,
			GetDesktopWindow(), nullptr, g_hInstance, nullptr);
		if (!m_hwnd)
			return E_FAIL;

		if (nullptr == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
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

		if (FAILED(m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE)))
			return E_FAIL;
	
		if (!MySingleton<Time>::GetSingleton()->Init())
			return E_FAIL;

		if (!MySingleton<Input>::GetSingleton()->Init())
			return E_FAIL;

		if (!MySingleton<AudioManager>::GetSingleton()->Init())
			return E_FAIL;

		MySingleton<SceneManager>::GetSingleton()->Init();
		MySingleton<SceneManager>::GetSingleton()->ChangeScene(new LogoScene);
#ifdef _DEBUG
		m_FPS = MySingleton<Assets>::GetSingleton()->RequestFont("Arial", 14);
#endif
		return S_OK;
	}

	void Engine::OnCleanUp()
	{
		SRELEASE(m_pd3dDevice);
		SRELEASE(m_pD3D);
	}

	void Engine::OnRender()
	{
		if (nullptr == m_pd3dDevice)
			return;

		m_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET, Colours::White, 1.0f, 0);
		if (SUCCEEDED(m_pd3dDevice->BeginScene()))
		{
			MySingleton<SceneManager>::GetSingleton()->Render();
#ifdef DEBUG
			Graphics::RenderText(*m_FPS, 10, 10, "frameRate: %ld", MySingleton<Time>::GetSingleton()->frameRate());
#endif
			m_pd3dDevice->EndScene();
		}

		m_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);
	}

	void Engine::OnUpdate(float delta)
	{
		MySingleton<SceneManager>::GetSingleton()->Update(delta);
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
			if (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
			else
			{
				MySingleton<Time>::GetSingleton()->Start();
				MySingleton<Input>::GetSingleton()->Capture();
				MySingleton<AudioManager>::GetSingleton()->AudioSystem()->update();
				OnRender();
				OnUpdate(MySingleton<Time>::GetSingleton()->deltaTime());
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
				PostQuitMessage(0);
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
		return MySingleton<Engine>::GetSingleton()->WndProc(hWnd, msg, wParam, lParam);
	}
}
