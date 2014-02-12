#include "Precompiled.h"

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE, LPSTR, int)
{
	Engine engine(hThisInstance);
	return engine.Run();
}