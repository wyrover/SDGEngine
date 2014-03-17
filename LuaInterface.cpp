#include "Precompiled.h"

namespace SDGEngine
{
	namespace Lua
	{
		void DumpStack(lua_State* L)
		{
			int top = lua_gettop(L);
			printf("========================================\n");
			for (int i = top; i >= 1; --i)
			{
				printf("%02d | ", i);
				switch (lua_type(L, i))
				{
				case LUA_TNIL:
					printf("nil      | \n");
					break;
				case LUA_TBOOLEAN:
					printf("boolean  | %d\n", (int)lua_toboolean(L, i));
					break;
				case LUA_TNUMBER:
					printf("number   | %f\n", lua_tonumber(L, i));
					break;
				case LUA_TSTRING:
					printf("string   | %s\n", lua_tostring(L, i));
					break;
				case LUA_TTABLE:
					printf("table    | 0x%08x\n", (int)lua_topointer(L, i));
					break;
				case LUA_TFUNCTION:
					printf("function | 0x%08x\n", (int)lua_topointer(L, i));
					break;
				case LUA_TUSERDATA:
					printf("userdata | 0x%08x\n", (int)lua_topointer(L, i));
					break;
				case LUA_TTHREAD:
					printf("thread   | 0x%08x\n", (int)lua_topointer(L, i));
					break;
				default:
					printf("unknown  | \n");
					break;
				}
			}
			printf("========================================\n");
		}

		void GenericToLua(lua_State *L, Variable& var)
		{
			Variable *reference = (Variable *)lua_newuserdata(L, sizeof(Variable));
			new (reference)Variable(var);
			lua_getglobal(L, var.Meta()->LuaMetaTable());
			lua_setmetatable(L, -2);
		}

		void GenericFromLua(lua_State *L, int index, Variable *var)
		{
			assert(lua_isuserdata(L, index));
			*var = *((Variable *)lua_touserdata(L, index));
		}

		int GenericFunc(lua_State *L)
		{
			Function *fn = (Function *)lua_touserdata(L, lua_upvalueindex(1));
			assert(fn);

			unsigned argCount = lua_gettop(L);
			assert(fn->Signature()->getArgc() == argCount);

			const MetaData *retType = fn->Signature()->getRet();
			bool returns = retType ? true : false;
			Variable ret;
			if (returns)
			{
				// Allocate space for the return value on the stack
				ret = Variable(fn->Signature()->getRet(), alloca(fn->Signature()->getRet()->Size()));
				// Run default constructor for return type
				ret.PlacementNew();
			}

			// Allocate space for the arguments and placement new defaults
			Variable *stackArgs = (Variable *)alloca(sizeof(Variable)* argCount);

			for (unsigned i = 0; i < argCount; ++i)
			{
				new (stackArgs + i) Variable(fn->Signature()->getArgs(i), alloca(fn->Signature()->getArgs(i)->Size()));
				stackArgs[i].PlacementNew();
			}

			// Load all arguments from the lua stack
			for (unsigned i = 0; i < argCount; ++i)
				stackArgs[i].FromLua(L, i + 1);

			// Call function
			(*fn)(ret, stackArgs, argCount);

			// Run destructors on the arguments
			for (unsigned i = 0; i < argCount; ++i)
				stackArgs[i].PlacementDelete();

			if (returns)
			{
				ret.ToLua(L);
				// Destructor for return value
				ret.PlacementDelete();
				return 1;
			}

			return 0;
		}

		int ErrorFunc(lua_State *L)
		{
			printf("Lua error occurred! %s", lua_tostring(L, -1));
			lua_pop(L, 1); // pop the error string
			return 0;
		}

		void CallFuncFinal(lua_State *L, const char *funcName, Variable *args, unsigned argCount)
		{
			lua_pushcfunction(L, ErrorFunc); // Stack index: 1

			lua_getglobal(L, funcName); // Stack index: 2

			for (unsigned i = 0; i < argCount; ++i)
			{
				args[i].ToLua(L);
			}

			int LuaErrorFuncIndex = -((int)(argCount + 2));
			lua_pcall(L, argCount, 1, LuaErrorFuncIndex);
			lua_remove(L, lua_gettop(L) - 1); // Pop error function or error data
			lua_settop(L, 0);
		}

		void CallFunc(lua_State *L, const char *funcName)
		{
			CallFuncFinal(L, funcName, NULL, 0);
		}

		void LoadLuaFile(lua_State *L, std::string &path)
		{
			std::string name = Singleton<Assets>::GetSingleton()->GetContentPath() + path;
			if (luaL_dofile(L, name.c_str()))
			{
				ErrorFunc(L);
			}
		}

		lua_State *CreateEnvironment(std::string &str)
		{
			lua_State *Lua = lua_open();
			luaL_openlibs(Lua);

			LoadLuaFile(Lua, str);

			return Lua;
		}

		void BindFunctionToLua(lua_State *L, Function *fn, const char *name)
		{
			lua_pushlightuserdata(L, fn);
			lua_pushcclosure(L, Lua::GenericFunc, 1);
			lua_setglobal(L, name);
		}
	}
}
