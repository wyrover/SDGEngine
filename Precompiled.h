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
#pragma comment(lib, "tinyxml/tinyxml.lib")
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
#include <queue>
#include <typeinfo>
#include <typeindex>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <imm.h>
#include "tinyxml.h"

#define randomize() srand((unsigned)time(nullptr))
#define random(n) (rand() % (n))

#define SDELETE(p)       { if(p) { delete (p);     (p)=nullptr; } }
#define SDELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=nullptr; } }
#define SRELEASE(p)      { if(p) { (p)->Release(); (p)=nullptr; } }
#define UNUSED(p) (void)p

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

namespace Colours
{
	const D3DCOLOR Maroon = D3DCOLOR_ARGB(255, 128, 0, 0);					//D3DCOLOR_ARGB(255, 128, 0, 0)
	const D3DCOLOR DarkRed = D3DCOLOR_ARGB(255, 139, 0, 0);					//D3DCOLOR_ARGB(255, 139, 0, 0)
	const D3DCOLOR Brown = D3DCOLOR_ARGB(255, 165, 42, 42);					//D3DCOLOR_ARGB(255, 165, 42, 42)
	const D3DCOLOR Firebrick = D3DCOLOR_ARGB(255, 178, 34, 34);				//D3DCOLOR_ARGB(255, 178, 34, 34)
	const D3DCOLOR Crimson = D3DCOLOR_ARGB(255, 220, 20, 60);				//D3DCOLOR_ARGB(255, 220, 20, 60)
	const D3DCOLOR Red = D3DCOLOR_ARGB(255, 255, 0, 0);						//D3DCOLOR_ARGB(255, 255, 0, 0)
	const D3DCOLOR Tomato = D3DCOLOR_ARGB(255, 255, 99, 71);				//D3DCOLOR_ARGB(255, 255, 99, 71)
	const D3DCOLOR Coral = D3DCOLOR_ARGB(255, 255, 127, 80);				//D3DCOLOR_ARGB(255, 255, 127, 80)
	const D3DCOLOR IndianRed = D3DCOLOR_ARGB(255, 205, 92, 92);				//D3DCOLOR_ARGB(255, 205, 92, 92)
	const D3DCOLOR LightCoral = D3DCOLOR_ARGB(255, 240, 128, 128);			//D3DCOLOR_ARGB(255, 240, 128, 128)
	const D3DCOLOR DarkSalmon = D3DCOLOR_ARGB(255, 233, 150, 122);			//D3DCOLOR_ARGB(255, 233, 150, 122)
	const D3DCOLOR Salmon = D3DCOLOR_ARGB(255, 250, 128, 114);				//D3DCOLOR_ARGB(255, 250, 128, 114)
	const D3DCOLOR LightSalmon = D3DCOLOR_ARGB(255, 255, 160, 122);			//D3DCOLOR_ARGB(255, 255, 160, 122)
	const D3DCOLOR OrangeRed = D3DCOLOR_ARGB(255, 255, 69, 0);				//D3DCOLOR_ARGB(255, 255, 69, 0)
	const D3DCOLOR DarkOrange = D3DCOLOR_ARGB(255, 255, 140, 0);			//D3DCOLOR_ARGB(255, 255, 140, 0)
	const D3DCOLOR Orange = D3DCOLOR_ARGB(255, 255, 165, 0);				//D3DCOLOR_ARGB(255, 255, 165, 0)
	const D3DCOLOR Gold = D3DCOLOR_ARGB(255, 255, 215, 0);					//D3DCOLOR_ARGB(255, 255, 215, 0)
	const D3DCOLOR DarkGoldenrod = D3DCOLOR_ARGB(255, 184, 134, 11);		//D3DCOLOR_ARGB(255, 184, 134, 11)
	const D3DCOLOR Goldenrod = D3DCOLOR_ARGB(255, 218, 165, 32);			//D3DCOLOR_ARGB(255, 218, 165, 32)
	const D3DCOLOR PaleGoldenrod = D3DCOLOR_ARGB(255, 238, 232, 170);		//D3DCOLOR_ARGB(255, 238, 232, 170)
	const D3DCOLOR DarkKhaki = D3DCOLOR_ARGB(255, 189, 183, 107);			//D3DCOLOR_ARGB(255, 189, 183, 107)
	const D3DCOLOR Khaki = D3DCOLOR_ARGB(255, 240, 230, 140);				//D3DCOLOR_ARGB(255, 240, 230, 140)
	const D3DCOLOR Olive = D3DCOLOR_ARGB(255, 128, 128, 0);					//D3DCOLOR_ARGB(255, 128, 128, 0)
	const D3DCOLOR Yellow = D3DCOLOR_ARGB(255, 255, 255, 0);				//D3DCOLOR_ARGB(255, 255, 255, 0)
	const D3DCOLOR YellowGreen = D3DCOLOR_ARGB(255, 154, 205, 50);			//D3DCOLOR_ARGB(255, 154, 205, 50)
	const D3DCOLOR DarkOliveGreen = D3DCOLOR_ARGB(255, 85, 107, 47);		//D3DCOLOR_ARGB(255, 85, 107, 47)
	const D3DCOLOR OliveDrab = D3DCOLOR_ARGB(255, 107, 142, 35);			//D3DCOLOR_ARGB(255, 107, 142, 35)
	const D3DCOLOR LawnGreen = D3DCOLOR_ARGB(255, 124, 252, 0);				//D3DCOLOR_ARGB(255, 124, 252, 0)
	const D3DCOLOR ChartReuse = D3DCOLOR_ARGB(255, 127, 255, 0);			//D3DCOLOR_ARGB(255, 127, 255, 0)
	const D3DCOLOR GreenYellow = D3DCOLOR_ARGB(255, 173, 255, 47);			//D3DCOLOR_ARGB(255, 173, 255, 47)
	const D3DCOLOR DarkGreen = D3DCOLOR_ARGB(255, 0, 100, 0);				//D3DCOLOR_ARGB(255, 0, 100, 0)
	const D3DCOLOR Green = D3DCOLOR_ARGB(255, 0, 128, 0);					//D3DCOLOR_ARGB(255, 0, 128, 0)
	const D3DCOLOR ForestGreen = D3DCOLOR_ARGB(255, 34, 139, 34);			//D3DCOLOR_ARGB(255, 34, 139, 34)
	const D3DCOLOR Lime = D3DCOLOR_ARGB(255, 0, 255, 0);					//D3DCOLOR_ARGB(255, 0, 255, 0)
	const D3DCOLOR LimeGreen = D3DCOLOR_ARGB(255, 50, 205, 50);				//D3DCOLOR_ARGB(255, 50, 205, 50)
	const D3DCOLOR LightGreen = D3DCOLOR_ARGB(255, 144, 238, 144);			//D3DCOLOR_ARGB(255, 144, 238, 144)
	const D3DCOLOR PaleGreen = D3DCOLOR_ARGB(255, 152, 251, 152);			//D3DCOLOR_ARGB(255, 152, 251, 152)
	const D3DCOLOR DarkSeaGreen = D3DCOLOR_ARGB(255, 143, 188, 143);		//D3DCOLOR_ARGB(255, 143, 188, 143)
	const D3DCOLOR MediumSpringGreen = D3DCOLOR_ARGB(255, 0, 250, 154);		//D3DCOLOR_ARGB(255, 0, 250, 154)
	const D3DCOLOR SpringGreen = D3DCOLOR_ARGB(255, 0, 255, 127);			//D3DCOLOR_ARGB(255, 0, 255, 127)
	const D3DCOLOR SeaGreen = D3DCOLOR_ARGB(255, 46, 139, 87);				//D3DCOLOR_ARGB(255, 46, 139, 87)
	const D3DCOLOR MediumAquaMarine = D3DCOLOR_ARGB(255, 102, 205, 170);	//D3DCOLOR_ARGB(255, 102, 205, 170)
	const D3DCOLOR MediumSeaGreen = D3DCOLOR_ARGB(255, 60, 179, 113);		//D3DCOLOR_ARGB(255, 60, 179, 113)
	const D3DCOLOR LightSeaGreen = D3DCOLOR_ARGB(255, 32, 178, 170);		//D3DCOLOR_ARGB(255, 32, 178, 170)
	const D3DCOLOR DarkSlateGray = D3DCOLOR_ARGB(255, 47, 79, 79);			//D3DCOLOR_ARGB(255, 47, 79, 79)
	const D3DCOLOR Teal = D3DCOLOR_ARGB(255, 0, 128, 128);					//D3DCOLOR_ARGB(255, 0, 128, 128)
	const D3DCOLOR DarkCyan = D3DCOLOR_ARGB(255, 0, 139, 139);				//D3DCOLOR_ARGB(255, 0, 139, 139)
	const D3DCOLOR Aqua = D3DCOLOR_ARGB(255, 0, 255, 255);					//D3DCOLOR_ARGB(255, 0, 255, 255)
	const D3DCOLOR LightCyan = D3DCOLOR_ARGB(255, 224, 255, 255);			//D3DCOLOR_ARGB(255, 224, 255, 255)
	const D3DCOLOR DarkTurqoise = D3DCOLOR_ARGB(255, 0, 206, 209);			//D3DCOLOR_ARGB(255, 0, 206, 209)
	const D3DCOLOR Turqoise = D3DCOLOR_ARGB(255, 64, 224, 208);				//D3DCOLOR_ARGB(255, 64, 224, 208)
	const D3DCOLOR MediumTurqoise = D3DCOLOR_ARGB(255, 72, 209, 204);		//D3DCOLOR_ARGB(255, 72, 209, 204)
	const D3DCOLOR PaleTurqoise = D3DCOLOR_ARGB(255, 175, 238, 238);		//D3DCOLOR_ARGB(255, 175, 238, 238)
	const D3DCOLOR AquaMarine = D3DCOLOR_ARGB(255, 127, 255, 212);			//D3DCOLOR_ARGB(255, 127, 255, 212)
	const D3DCOLOR PowderBlue = D3DCOLOR_ARGB(255, 176, 224, 230);			//D3DCOLOR_ARGB(255, 176, 224, 230)
	const D3DCOLOR CadetBlue = D3DCOLOR_ARGB(255, 95, 158, 160);			//D3DCOLOR_ARGB(255, 95, 158, 160)
	const D3DCOLOR SteelBlue = D3DCOLOR_ARGB(255, 70, 130, 180);			//D3DCOLOR_ARGB(255, 70, 130, 180)
	const D3DCOLOR CornflowerBlue = D3DCOLOR_ARGB(255, 100, 149, 237);		//D3DCOLOR_ARGB(255, 100, 149, 237)
	const D3DCOLOR DeepSkyBlue = D3DCOLOR_ARGB(255, 0, 191, 255);			//D3DCOLOR_ARGB(255, 0, 191, 255)
	const D3DCOLOR DodgerBlue = D3DCOLOR_ARGB(255, 30, 144, 255);			//D3DCOLOR_ARGB(255, 30, 144, 255)
	const D3DCOLOR LightBlue = D3DCOLOR_ARGB(255, 173, 216, 230);			//D3DCOLOR_ARGB(255, 173, 216, 230)
	const D3DCOLOR SkyBlue = D3DCOLOR_ARGB(255, 135, 206, 250);				//D3DCOLOR_ARGB(255, 135, 206, 250)
	const D3DCOLOR LightSkyBlue = D3DCOLOR_ARGB(255, 135, 206, 250);		//D3DCOLOR_ARGB(255, 135, 206, 250)
	const D3DCOLOR MidnightBlue = D3DCOLOR_ARGB(255, 25, 25, 112);			//D3DCOLOR_ARGB(255, 25, 25, 112)
	const D3DCOLOR Navy = D3DCOLOR_ARGB(255, 0, 0, 128);					//D3DCOLOR_ARGB(255, 0, 0, 128)
	const D3DCOLOR DarkBlue = D3DCOLOR_ARGB(255, 0, 0, 139);				//D3DCOLOR_ARGB(255, 0, 0, 139)
	const D3DCOLOR MediumBlue = D3DCOLOR_ARGB(255, 0, 0, 205);				//D3DCOLOR_ARGB(255, 0, 0, 205)
	const D3DCOLOR Blue = D3DCOLOR_ARGB(255, 0, 0, 255);					//D3DCOLOR_ARGB(255, 0, 0, 255)
	const D3DCOLOR RoyalBlue = D3DCOLOR_ARGB(255, 65, 105, 225);			//D3DCOLOR_ARGB(255, 65, 105, 225)
	const D3DCOLOR BlueViolet = D3DCOLOR_ARGB(255, 138, 43, 226);			//D3DCOLOR_ARGB(255, 138, 43, 226)
	const D3DCOLOR Indigo = D3DCOLOR_ARGB(255, 75, 0, 130);					//D3DCOLOR_ARGB(255, 75, 0, 130)
	const D3DCOLOR DarkSlateBlue = D3DCOLOR_ARGB(255, 72, 61, 139);			//D3DCOLOR_ARGB(255, 72, 61, 139)
	const D3DCOLOR SlateBlue = D3DCOLOR_ARGB(255, 106, 90, 205);			//D3DCOLOR_ARGB(255, 106, 90, 205)
	const D3DCOLOR MediumSlateBlue = D3DCOLOR_ARGB(255, 123, 104, 238);		//D3DCOLOR_ARGB(255, 123, 104, 238)
	const D3DCOLOR MediumPurple = D3DCOLOR_ARGB(255, 147, 112, 219);		//D3DCOLOR_ARGB(255, 147, 112, 219)
	const D3DCOLOR DarkMagenta = D3DCOLOR_ARGB(255, 139, 0, 139);			//D3DCOLOR_ARGB(255, 139, 0, 139)
	const D3DCOLOR DarkViolet = D3DCOLOR_ARGB(255, 149, 0, 211);			//D3DCOLOR_ARGB(255, 149, 0, 211)
	const D3DCOLOR DarkOrchid = D3DCOLOR_ARGB(255, 153, 50, 204);			//D3DCOLOR_ARGB(255, 153, 50, 204)
	const D3DCOLOR MediumOrchid = D3DCOLOR_ARGB(255, 186, 85, 211);			//D3DCOLOR_ARGB(255, 186, 85, 211)
	const D3DCOLOR Purple = D3DCOLOR_ARGB(255, 128, 0, 128);				//D3DCOLOR_ARGB(255, 128, 0, 128)
	const D3DCOLOR Thistle = D3DCOLOR_ARGB(255, 216, 191, 216);				//D3DCOLOR_ARGB(255, 216, 191, 216)
	const D3DCOLOR Plum = D3DCOLOR_ARGB(255, 221, 160, 221);				//D3DCOLOR_ARGB(255, 221, 160, 221)
	const D3DCOLOR Violet = D3DCOLOR_ARGB(255, 238, 130, 238);				//D3DCOLOR_ARGB(255, 238, 130, 238)
	const D3DCOLOR Magenta = D3DCOLOR_ARGB(255, 255, 0, 255);				//D3DCOLOR_ARGB(255, 255, 0, 255)
	const D3DCOLOR Orchid = D3DCOLOR_ARGB(255, 218, 112, 214);				//D3DCOLOR_ARGB(255, 218, 112, 214)
	const D3DCOLOR MediumVioletRed = D3DCOLOR_ARGB(255, 199, 21, 133);		//D3DCOLOR_ARGB(255, 199, 21, 133)
	const D3DCOLOR PaleVioletRed = D3DCOLOR_ARGB(255, 219, 112, 147);		//D3DCOLOR_ARGB(255, 219, 112, 147)
	const D3DCOLOR DeepPink = D3DCOLOR_ARGB(255, 255, 20, 147);				//D3DCOLOR_ARGB(255, 255, 20, 147)
	const D3DCOLOR HotPink = D3DCOLOR_ARGB(255, 255, 105, 180);				//D3DCOLOR_ARGB(255, 255, 105, 180)
	const D3DCOLOR LightPink = D3DCOLOR_ARGB(255, 255, 182, 193);			//D3DCOLOR_ARGB(255, 255, 182, 193)
	const D3DCOLOR Pink = D3DCOLOR_ARGB(255, 255, 192, 203);				//D3DCOLOR_ARGB(255, 255, 192, 203)
	const D3DCOLOR AntiqueWhite = D3DCOLOR_ARGB(255, 250, 235, 215);		//D3DCOLOR_ARGB(255, 250, 235, 215)
	const D3DCOLOR Beige = D3DCOLOR_ARGB(255, 245, 245, 220);				//D3DCOLOR_ARGB(255, 245, 245, 220)
	const D3DCOLOR Bisque = D3DCOLOR_ARGB(255, 255, 228, 196);				//D3DCOLOR_ARGB(255, 255, 228, 196)
	const D3DCOLOR BlanchedAlmond = D3DCOLOR_ARGB(255, 255, 235, 205);		//D3DCOLOR_ARGB(255, 255, 235, 205)
	const D3DCOLOR Wheat = D3DCOLOR_ARGB(255, 245, 222, 179);				//D3DCOLOR_ARGB(255, 245, 222, 179)
	const D3DCOLOR CornSilk = D3DCOLOR_ARGB(255, 255, 248, 220);			//D3DCOLOR_ARGB(255, 255, 248, 220)
	const D3DCOLOR LemonChiffon = D3DCOLOR_ARGB(255, 255, 250, 205);		//D3DCOLOR_ARGB(255, 255, 250, 205)
	const D3DCOLOR LightGoldenrodYellow = D3DCOLOR_ARGB(255, 250, 250, 210);//D3DCOLOR_ARGB(255, 250, 250, 210)
	const D3DCOLOR LightYellow = D3DCOLOR_ARGB(255, 255, 255, 224);			//D3DCOLOR_ARGB(255, 255, 255, 224)
	const D3DCOLOR SaddieBrown = D3DCOLOR_ARGB(255, 139, 69, 19);			//D3DCOLOR_ARGB(255, 139, 69, 19)
	const D3DCOLOR Sienna = D3DCOLOR_ARGB(255, 160, 82, 45);				//D3DCOLOR_ARGB(255, 160, 82, 45)
	const D3DCOLOR Chocolate = D3DCOLOR_ARGB(255, 210, 105, 30);			//D3DCOLOR_ARGB(255, 210, 105, 30)
	const D3DCOLOR Peru = D3DCOLOR_ARGB(255, 205, 133, 63);					//D3DCOLOR_ARGB(255, 205, 133, 63)
	const D3DCOLOR SandyBrown = D3DCOLOR_ARGB(255, 244, 164, 96);			//D3DCOLOR_ARGB(255, 244, 164, 96)
	const D3DCOLOR BurlyWood = D3DCOLOR_ARGB(255, 222, 184, 135);			//D3DCOLOR_ARGB(255, 222, 184, 135)
	const D3DCOLOR Tan = D3DCOLOR_ARGB(255, 210, 180, 140);					//D3DCOLOR_ARGB(255, 210, 180, 140)
	const D3DCOLOR RosyBrown = D3DCOLOR_ARGB(255, 188, 143, 143);			//D3DCOLOR_ARGB(255, 188, 143, 143)
	const D3DCOLOR Moccasin = D3DCOLOR_ARGB(255, 255, 228, 181);			//D3DCOLOR_ARGB(255, 255, 228, 181)
	const D3DCOLOR NavajoWhite = D3DCOLOR_ARGB(255, 255, 222, 173);			//D3DCOLOR_ARGB(255, 255, 222, 173)
	const D3DCOLOR PeachPuff = D3DCOLOR_ARGB(255, 255, 218, 185);			//D3DCOLOR_ARGB(255, 255, 218, 185)
	const D3DCOLOR MistyRose = D3DCOLOR_ARGB(255, 255, 228, 225);			//D3DCOLOR_ARGB(255, 255, 228, 225)
	const D3DCOLOR LavenderBlush = D3DCOLOR_ARGB(255, 255, 240, 245);		//D3DCOLOR_ARGB(255, 255, 240, 245)
	const D3DCOLOR Linen = D3DCOLOR_ARGB(255, 250, 240, 230);				//D3DCOLOR_ARGB(255, 250, 240, 230)
	const D3DCOLOR OldLace = D3DCOLOR_ARGB(255, 253, 245, 230);				//D3DCOLOR_ARGB(255, 253, 245, 230)
	const D3DCOLOR PapayaWhip = D3DCOLOR_ARGB(255, 255, 239, 213);			//D3DCOLOR_ARGB(255, 255, 239, 213)
	const D3DCOLOR SeaShell = D3DCOLOR_ARGB(255, 255, 245, 238);			//D3DCOLOR_ARGB(255, 255, 245, 238)
	const D3DCOLOR MintCream = D3DCOLOR_ARGB(255, 245, 255, 250);			//D3DCOLOR_ARGB(255, 245, 255, 250)
	const D3DCOLOR SlateGray = D3DCOLOR_ARGB(255, 112, 128, 144);			//D3DCOLOR_ARGB(255, 112, 128, 144)
	const D3DCOLOR LightSlateGray = D3DCOLOR_ARGB(255, 119, 136, 153);		//D3DCOLOR_ARGB(255, 119, 136, 153)
	const D3DCOLOR LightSteelBlue = D3DCOLOR_ARGB(255, 176, 196, 222);		//D3DCOLOR_ARGB(255, 176, 196, 222)
	const D3DCOLOR Lavender = D3DCOLOR_ARGB(255, 230, 230, 250);			//D3DCOLOR_ARGB(255, 230, 230, 250)
	const D3DCOLOR FloralWhite = D3DCOLOR_ARGB(255, 255, 250, 240);			//D3DCOLOR_ARGB(255, 255, 250, 240)
	const D3DCOLOR AliceBlue = D3DCOLOR_ARGB(255, 240, 248, 255);			//D3DCOLOR_ARGB(255, 240, 248, 255)
	const D3DCOLOR GhostWhite = D3DCOLOR_ARGB(255, 248, 248, 255);			//D3DCOLOR_ARGB(255, 248, 248, 255)
	const D3DCOLOR Honeydew = D3DCOLOR_ARGB(255, 240, 255, 240);			//D3DCOLOR_ARGB(255, 240, 255, 240)
	const D3DCOLOR Ivory = D3DCOLOR_ARGB(255, 255, 255, 240);				//D3DCOLOR_ARGB(255, 255, 255, 240)
	const D3DCOLOR Azure = D3DCOLOR_ARGB(255, 240, 255, 255);				//D3DCOLOR_ARGB(255, 240, 255, 255)
	const D3DCOLOR Snow = D3DCOLOR_ARGB(255, 255, 250, 250);				//D3DCOLOR_ARGB(255, 255, 250, 250)
	const D3DCOLOR Black = D3DCOLOR_ARGB(255, 0, 0, 0);						//D3DCOLOR_ARGB(255, 0, 0, 0)
	const D3DCOLOR DimGray = D3DCOLOR_ARGB(255, 105, 105, 105);				//D3DCOLOR_ARGB(255, 105, 105, 105)
	const D3DCOLOR Gray = D3DCOLOR_ARGB(255, 128, 128, 128);				//D3DCOLOR_ARGB(255, 128, 128, 128)
	const D3DCOLOR DarkGray = D3DCOLOR_ARGB(255, 169, 169, 169);			//D3DCOLOR_ARGB(255, 169, 169, 169)
	const D3DCOLOR Silver = D3DCOLOR_ARGB(255, 192, 192, 192);				//D3DCOLOR_ARGB(255, 192, 192, 192)
	const D3DCOLOR LightGray = D3DCOLOR_ARGB(255, 211, 211, 211);			//D3DCOLOR_ARGB(255, 211, 211, 211)
	const D3DCOLOR Gainsboro = D3DCOLOR_ARGB(255, 220, 220, 220);			//D3DCOLOR_ARGB(255, 220, 220, 220)
	const D3DCOLOR WhiteSmoke = D3DCOLOR_ARGB(255, 245, 245, 245);			//D3DCOLOR_ARGB(255, 245, 245, 245)
	const D3DCOLOR White = D3DCOLOR_ARGB(255, 255, 255, 255);				//D3DCOLOR_ARGB(255, 255, 255, 255)
}

#include "Object.h"
#include "Debug.h"
#include "File.h"
#include "XMLFileNode.h"
#include "Asset.h"
#include "Assets.h"
#include "TextureAsset.h"
#include "TextureAtlas.h"
//#include "AudioAsset.h"
//#include "TTFFontAsset.h"
#include "FontAsset.h"
#include "MemPooler.h"
#include "Input.h"
#include "Time.h"
#include "Graphics.h"
#include "Bounds.h"
#include "Sprite.h"
#include "AnimationClip.h"
#include "AnimationEnums.h"
#include "MessageEnums.h"
#include "Message.h"
#include "Space.h"
#include "Component.h"
#include "GameObject.h"
#include "GameScene.h"
#include "SceneQueue.h"
#include "Engine.h"

#include "Ime.h"

#include "Collider.h"
#include "Renderer.h"
#include "Behaviour.h"
#include "SpriteRenderer.h"
#include "Controller.h"
#include "Animation.h"

#include "LogoScene.h"
#include "TitleScene.h"

#ifdef _DEBUG
#include "vld.h"
#endif