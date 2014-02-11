#include "Precompiled.h"

Engine *ENGINE = nullptr;
Engine::Engine()
{
	ENGINE = this;
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
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hwnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pd3dDevice)))
		return E_FAIL;

	m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_lua = Lua::CreateEnvironment();

	renderer = new Renderer;
	GameObject *hero = new GameObject(&space, "hero");
	auto obj1 = hero->AddComponent<TextComponent>();
	obj1->setText("hello component based object management!");
	hero->SubscribeToMessageType<TextComponent>(MT_OBJECT_CREATED);
	hero->SubscribeToMessageType<TextComponent>(MT_UPDATE);

	Message msg(MT_OBJECT_CREATED);
	hero->BroadcastMessage(msg);
	//hero->SetActiveRecursively(true);

	space.Init();

	return S_OK;
}

void Engine::OnCleanUp()
{
	space.Destroy();
	delete renderer;
	renderer = nullptr;

	if (m_pd3dDevice != nullptr)
		m_pd3dDevice->Release();

	if (m_pD3D != nullptr)
		m_pD3D->Release();
}

void Engine::OnRender()
{
	if (nullptr == m_pd3dDevice)
		return;

	m_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	if (SUCCEEDED(m_pd3dDevice->BeginScene()))
	{
		space.Render();
		m_pd3dDevice->EndScene();
	}

	m_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

void Engine::OnUpdate(float delta)
{
	space.Update(delta);
}

int Engine::Run()
{
	if (FAILED(OnInit()))
		return 0;

	ShowWindow(m_hwnd, SW_SHOWDEFAULT);
	UpdateWindow(m_hwnd);

	//Store counts per second
	__int64 countsPerSec = 0;
	BOOL ret = QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	if (!ret) return 0;

	float secPerCount = 1.0f / countsPerSec; //store seconds per count

	//Initial previous time
	__int64 prevTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&prevTime);

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
			//Capture current count
			__int64 curTime = 0;
			QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
			//Calculate deltaTime
			float deltaTime = (curTime - prevTime) * secPerCount;

			CalculateFPS(deltaTime);
			OnRender();
			OnUpdate(deltaTime);

			prevTime = curTime;
		}
	}

	UnregisterClass(m_caption.c_str(), m_hInst);

	return 0;
}

LRESULT Engine::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
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

void Engine::CalculateFPS(float dt)
{
	static int frameCnt;
	static float elapsedTime;

	//Increment frameCnt
	frameCnt++;
	//Increment elapsed time
	elapsedTime += dt;

	if (elapsedTime >= 1.0f)
	{
		m_FPS = (float)frameCnt;

		//Output FPS to Window title
		std::stringstream ss;
		ss << m_caption.c_str() << " FPS:  " << m_FPS;
		SetWindowText(m_hwnd, ss.str().c_str());

		//Reset elapsed time and frame count
		frameCnt = 0;
		elapsedTime = 0;
	}
}
