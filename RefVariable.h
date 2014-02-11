#pragma once

class RefVariable : public VariableBase
{
public:
	RefVariable();
	template<typename T>
	RefVariable( const T& value );
	RefVariable( const RefVariable& rhs );
	RefVariable( const Variable& rhs );
	RefVariable( const MetaData *m, void *d );

	RefVariable& operator =( const RefVariable& rhs );
	RefVariable& operator =( const Variable& rhs );
	template<typename T>
	RefVariable& operator =( const T& rhs );
};

template<typename T>
RefVariable& RefVariable::operator=( const T& rhs )
{
	meta = META_TYPE( T );
	data = const_cast<T *>(&rhs);
	return *this;
}

template<typename T>
RefVariable::RefVariable( const T& value )
	:VariableBase( META_TYPE(T), const_cast<T *>(&value) )
{
}
