#include "Precompiled.h"

Engine *ENGINE = nullptr;
Engine::Engine(HINSTANCE inst)
{
	ENGINE = this;
	m_hInst = inst;
	m_dwStyle = WS_CAPTION | WS_SYSMENU;
	m_caption = "Test application";
	m_dwScreenWidth = 1024;
	m_dwScreenHeight = 800;
}

Engine::~Engine()
{
	ENGINE = nullptr;
	lua_close(m_lua);
}

HRESULT Engine::OnInit()
{
	Lua::DefaultRegistration();
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
		GetDesktopWindow(), nullptr, m_hInst, nullptr);

	if (nullptr == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hwnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pd3dDevice)))
		return E_FAIL;

	m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_lua = Lua::CreateEnvironment();

	time = new Time;
	input = new Input;
	frameRateFont = new Font("Arial", 15);
	addSceneFromQueue(new LogoScene);

	return S_OK;
}

void Engine::OnCleanUp()
{
	deleteAllFromRemovedQueue();
	SDELETE(frameRateFont);
	SDELETE(time);
	SDELETE(input);
	SRELEASE(m_pd3dDevice);
	SRELEASE(m_pD3D);
}

void Engine::OnRender()
{
	if (nullptr == m_pd3dDevice)
		return;

	m_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	if (SUCCEEDED(m_pd3dDevice->BeginScene()))
	{
		frameRateFont->PrintFormat(10, 20, "frameRate: %ld", time->frameRate());
		if (getSceneQueueSize() != 0)
		{
			GameScene *scene = m_SceneQueue.back();
			if (scene && !scene->isFinished() && scene->isActive())
			{
				scene->Render();
			}
			else if (scene->isFinished())
			{
				removeSceneFromQueue();
			}
		}
		m_pd3dDevice->EndScene();
	}

	m_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

void Engine::OnUpdate(float delta)
{
	if (getSceneQueueSize() != 0)
	{
		GameScene *scene = m_SceneQueue.back();
		if (scene && !scene->isFinished() && scene->isActive())
		{
			scene->Update(delta);
		}
		else if (scene->isFinished())
		{
			removeSceneFromQueue();
		}
	}
}

void Engine::addSceneFromQueue(GameScene *scene)
{
	scene->Init();
	m_SceneQueue.push(scene);
}

void Engine::removeSceneFromQueue()
{
	if (!m_SceneQueue.empty()) {
		m_RemovedSceneQueue.push(m_SceneQueue.back());
		m_SceneQueue.back()->Destroy();
		m_SceneQueue.pop();
	}
}

void Engine::removeAllSceneFromQueue()
{
	size_t size = getSceneQueueSize();
	for (unsigned i = 0; i < size; i++) {
		removeSceneFromQueue();
	}
}

void Engine::deleteAllFromRemovedQueue()
{
	removeAllSceneFromQueue();
	size_t size = m_RemovedSceneQueue.size();
	for (unsigned i = 0; i < size; i++) {
		SDELETE(m_RemovedSceneQueue.back());
		m_RemovedSceneQueue.pop();
	}
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
			time->MeasureTheTime();
			OnRender();
			OnUpdate(time->deltaTime());
		}
	}

	UnregisterClass(m_caption.c_str(), m_hInst);

	return 0;
}

LRESULT Engine::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
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
	return ENGINE->WndProc(hWnd, msg, wParam, lParam);
}
