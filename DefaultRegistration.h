#pragma once

DEFINE_META_POD(unsigned);
DEFINE_META_POD(unsigned *);
DEFINE_META_POD(int);
DEFINE_META_POD(int *);
DEFINE_META_POD(long);
DEFINE_META_POD(long *);
DEFINE_META_POD(float);
DEFINE_META_POD(float *);
DEFINE_META_POD(double);
DEFINE_META_POD(double *);
DEFINE_META_POD(bool);
DEFINE_META_POD(bool *);
DEFINE_META_POD(char);
DEFINE_META_POD(char *);
DEFINE_META_POD(std::string);

namespace Lua
{
	void IntToLua(lua_State *L, Variable& var);
	void IntFromLua(lua_State *L, int index, Variable *ref);
	void UnsignedToLua(lua_State *L, Variable& var);
	void UnsignedFromLua(lua_State *L, int index, Variable *ref);
	void LongToLua(lua_State *L, Variable& var);
	void LongFromLua(lua_State *L, int index, Variable *ref);
	void FloatToLua(lua_State *L, Variable& var);
	void FloatFromLua(lua_State *L, int index, Variable *ref);
	void DoubleToLua(lua_State *L, Variable& var);
	void DoubleFromLua(lua_State *L, int index, Variable *ref);
	void BoolToLua(lua_State *L, Variable& var);
	void BoolFromLua(lua_State *L, int index, Variable *ref);
	void CharPToLua(lua_State *L, Variable& var);
	void CharPFromLua(lua_State *L, int index, Variable *ref);
	void DefaultRegistration();
}
