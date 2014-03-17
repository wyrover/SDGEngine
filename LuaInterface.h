#pragma once

namespace SDGEngine
{
	namespace Lua
	{
		bool isChanged(LPCWSTR path);
		void DumpStack(lua_State* L);
		void GenericToLua(lua_State *L, Variable& var);
		void GenericFromLua(lua_State *L, int index, Variable *var);
		int GenericFunc(lua_State *L);
		int ErrorFunc(lua_State *L);
		void CallFuncFinal(lua_State *L, const char *funcName, Variable *args, unsigned argCount);
		void CallFunc(lua_State *L, const char *funcName);
		template <typename Arg1>
		void CallFunc(lua_State *L, const char *funcName, Arg1 arg1);
		template <typename Arg1, typename Arg2>
		void CallFunc(lua_State *L, const char *funcName, Arg1 arg1, Arg2 arg2);
		template <typename Arg1, typename Arg2, typename Arg3>
		void CallFunc(lua_State *L, const char *funcName, Arg1 arg1, Arg2 arg2, Arg3 arg3);
		template <typename Arg1, typename Arg2, typename Arg3, typename Arg4>
		void CallFunc(lua_State *L, const char *funcName, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4);
		template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
		void CallFunc(lua_State *L, const char *funcName, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5);
		void LoadLuaFile(lua_State *L, std::string &path);
		lua_State *CreateEnvironment(std::string &str);
		void BindFunctionToLua(lua_State *L, Function *fn, const char *name);

		template <typename Arg1>
		void CallFunc(lua_State *L, const char *funcName, Arg1 arg1)
		{
			Variable args[] = {
				arg1
			};

			CallFuncFinal(L, funcName, args, 1);
		}

		template <typename Arg1, typename Arg2>
		void CallFunc(lua_State *L, const char *funcName, Arg1 arg1, Arg2 arg2)
		{
			Variable args[] = {
				arg1,
				arg2
			};

			CallFuncFinal(L, funcName, args, 2);
		}

		template <typename Arg1, typename Arg2, typename Arg3>
		void CallFunc(lua_State *L, const char *funcName, Arg1 arg1, Arg2 arg2, Arg3 arg3)
		{
			Variable args[] = {
				arg1,
				arg2,
				arg3
			};

			CallFuncFinal(L, funcName, args, 3);
		}

		template <typename Arg1, typename Arg2, typename Arg3, typename Arg4>
		void CallFunc(lua_State *L, const char *funcName, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
		{
			Variable args[] = {
				arg1,
				arg2,
				arg3,
				arg4
			};

			CallFuncFinal(L, funcName, args, 4);
		}

		template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
		void CallFunc(lua_State *L, const char *funcName, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5)
		{
			Variable args[] = {
				arg1,
				arg2,
				arg3,
				arg4,
				arg5
			};

			CallFuncFinal(L, funcName, args, 5);
		}
	}
}
