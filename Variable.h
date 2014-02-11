#pragma once

class Variable : public VariableBase
{
public:
	Variable(void);
	template <typename T> 
	Variable(const T& rhs);
	template <typename T>
	Variable(const T *rhs);
	template <typename T>
	Variable(T *rhs);
	Variable( const MetaData *m, void *d );

	Variable& operator =( const Variable &rhs );

	void FromLua(lua_State *L, int index);
	void ToLua(lua_State *L) const;
	void PlacementNew(void);
	void PlacementDelete(void);
};

template <typename T>
Variable::Variable(T *rhs)
	: VariableBase( META_TYPE(T *), (T *)rhs)
{
}

template <typename T>
Variable::Variable(const T *rhs)
	: VariableBase( META_TYPE(T *), (T *)rhs)
{
}

template <typename T>
Variable::Variable(const T& rhs)
	: VariableBase( META_TYPE(T), (T *)&rhs )
{
}
