#include "Precompiled.h"

using namespace sidescroll;

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE, LPSTR, int)
{
	Engine engine(hThisInstance);
	return engine.Run();
}