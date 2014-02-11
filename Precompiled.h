#pragma once

#pragma warning(disable:4996)

#define WIN32_LEAN_AND_MEAN
#define DIRECTINPUT_VERSION 0x0800

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "xinput.lib")
#pragma comment(lib, "lua5.1.lib")
#pragma comment(lib, "lua51.lib")
#pragma comment(lib, "imm32.lib")
#pragma comment(lib, "vld.lib")

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <Windows.h>
#include <mmsystem.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <string>
#include <sstream>
#include <iostream>
#include <cassert>
#include <vector>
#include <unordered_map>
#include <set>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <imm.h>

#include "Input.h"
#include "MemPooler.h"
#include "RemoveQualifier.h"
#include "Meta.h"
#include "MetaMacro.h"
#include "VariableBase.h"
#include "Variable.h"
#include "RefVariable.h"
#include "TextSerialize.h"
#include "Function.h"
#include "LuaInterface.h"
#include "DefaultRegistration.h"

#include "Object.h"
#include "Texture.h"
#include "Graphics.h"
#include "AnimationClip.h"
#include "AnimationState.h"
#include "AnimationEnums.h"
#include "File.h"
#include "MessageEnums.h"
#include "Message.h"
#include "Space.h"
#include "Component.h"
#include "GameObject.h"
#include "GameScene.h"
#include "Engine.h"

#include "EditBox.h"

#include "TextComponent.h"
#include "Collider.h"
#include "Renderer.h"
#include "Behaviour.h"
#include "Animation.h"

#define randomize() srand((unsigned)time(NULL))
#define random(n) (rand() % (n))

#ifdef _DEBUG
#include "vld.h"
#endif