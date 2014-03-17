#include "Precompiled.h"

namespace SDGEngine
{
	RefVariable::RefVariable()
		: VariableBase(NULL, NULL)
	{
	}

	RefVariable::RefVariable(const RefVariable& rhs)
		: VariableBase(rhs.Meta(), rhs.Data())
	{
	}

	RefVariable::RefVariable(const Variable& rhs)
		: VariableBase(rhs.Meta(), rhs.Data())
	{
	}

	RefVariable::RefVariable(const MetaData *m, void *d)
		: VariableBase(m, d)
	{
	}

	RefVariable& RefVariable::operator=(const RefVariable& rhs)
	{
		meta = rhs.meta;
		data = rhs.data;
		return *this;
	}

	RefVariable& RefVariable::operator=(const Variable& rhs)
	{
		meta = rhs.Meta();
		data = rhs.Data();
		return *this;
	}
}
