sidescroll source
==========

*sidescroll game source using directx9.0 in c++*

feature
------------

- directx9.0 framework
- component based object management (stole Unity3D idea)
- C++ message system (communicate with component system)
- game scene management (using lua)
- integrated lua script
- meta data reflection, introspection
- generic function binder class
- auto lua function binding
- input method editer in win32api environment
- space system (contain gameobject unit)
- memory pool (using Hitel, gma 7 3 source)
- directinput8 wrapper class
- sprite animation (incomplete)

flaws
------------

- not multithreaded
- not cross platform (only in win32 operating system)

```C++
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE, LPSTR, int)
{
	Engine engine;
	return engine.Run();
}
```

*version 0.1 made by bodguy*
http://blog.naver.com/bodguy

*thanks*
