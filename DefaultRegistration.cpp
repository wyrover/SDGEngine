#include "Precompiled.h"

namespace sidescroll
{
	namespace Lua
	{
		void IntToLua(lua_State *L, Variable& var)
		{
			lua_pushinteger(L, var.GetValue<int>());
		}

		void IntFromLua(lua_State *L, int index, Variable *ref)
		{
			assert(lua_isnumber(L, index));
			int temp = lua_tointeger(L, index);
			ref->SetData(ref->Meta()->NewCopy(&temp));
		}

		void UnsignedToLua(lua_State *L, Variable& var)
		{
			lua_pushnumber(L, var.GetValue<unsigned>());
		}

		void UnsignedFromLua(lua_State *L, int index, Variable *ref)
		{
			assert(lua_isnumber(L, index));
			unsigned temp = (unsigned)lua_tonumber(L, index);
			ref->SetData(ref->Meta()->NewCopy(&temp));
		}

		void LongToLua(lua_State *L, Variable& var)
		{
			lua_pushnumber(L, var.GetValue<long>());
		}

		void LongFromLua(lua_State *L, int index, Variable *ref)
		{
			assert(lua_isnumber(L, index));
			long temp = (long)lua_tonumber(L, index);
			ref->SetData(ref->Meta()->NewCopy(&temp));
		}

		void FloatToLua(lua_State *L, Variable& var)
		{
			lua_pushnumber(L, var.GetValue<float>());
		}

		void FloatFromLua(lua_State *L, int index, Variable *ref)
		{
			assert(lua_isnumber(L, index));
			float temp = (float)lua_tonumber(L, index);
			ref->SetData(ref->Meta()->NewCopy(&temp));
		}

		void DoubleToLua(lua_State *L, Variable& var)
		{
			lua_pushnumber(L, var.GetValue<double>());
		}

		void DoubleFromLua(lua_State *L, int index, Variable *ref)
		{
			assert(lua_isnumber(L, index));
			double temp = (double)lua_tonumber(L, index);
			ref->SetData(ref->Meta()->NewCopy(&temp));
		}

		void BoolToLua(lua_State *L, Variable& var)
		{
			lua_pushboolean(L, var.GetValue<bool>());
		}

		void BoolFromLua(lua_State *L, int index, Variable *ref)
		{
			assert(lua_isboolean(L, index));
			int temp = lua_toboolean(L, index);
			ref->SetData(ref->Meta()->NewCopy(&temp));
		}

		void CharPToLua(lua_State *L, Variable& var)
		{
			lua_pushstring(L, var.GetValue<char*>());
		}

		void CharPFromLua(lua_State *L, int index, Variable *ref)
		{
			assert(lua_isstring(L, index));
			const char *temp = lua_tostring(L, index);
			*ref = temp;
		}

		void DefaultRegistration()
		{
			SET_TO_LUA(int, IntToLua);
			SET_FROM_LUA(int, IntFromLua);
			SET_TO_LUA(unsigned, UnsignedToLua);
			SET_FROM_LUA(unsigned, UnsignedFromLua);
			SET_TO_LUA(long, LongToLua);
			SET_FROM_LUA(long, LongFromLua);
			SET_TO_LUA(float, FloatToLua);
			SET_FROM_LUA(float, FloatFromLua);
			SET_TO_LUA(double, DoubleToLua);
			SET_FROM_LUA(double, DoubleFromLua);
			SET_TO_LUA(bool, BoolToLua);
			SET_FROM_LUA(bool, BoolFromLua);
			SET_TO_LUA(char *, CharPToLua);
			SET_FROM_LUA(char *, CharPFromLua);
		}
	}
}
