#include "Precompiled.h"

namespace sidescroll
{
	Variable::Variable(void)
		: VariableBase(NULL, NULL)
	{
	}

	Variable::Variable(const MetaData *m, void *d)
		: VariableBase(m, d)
	{

	}

	Variable& Variable::operator=(const Variable &rhs)
	{
		data = rhs.data;
		meta = rhs.meta;

		return *this;
	}

	void Variable::FromLua(lua_State *L, int index)
	{
		meta->FromLua(L, index, this);
	}

	void Variable::ToLua(lua_State *L) const
	{
		meta->ToLua(L, *this);
	}

	void Variable::PlacementNew(void)
	{
		meta->PlacementNew(data);
	}

	void Variable::PlacementDelete(void)
	{
		meta->PlacementDelete(data);
	}
}
