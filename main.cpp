#include "Precompiled.h"

using namespace sidescroll;

HINSTANCE g_hInstance;
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE, LPSTR, int)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	g_hInstance = hThisInstance;
	return MySingleton<Engine>::GetSingleton()->Run();
}