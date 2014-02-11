#include "Precompiled.h"

VariableBase::VariableBase(void)
	: meta(NULL), data(NULL)
{
}

VariableBase::VariableBase( const MetaData *m, void *d )
	: meta(m), data(d)
{

}

const MetaData * VariableBase::Meta() const
{
	return meta;
}

void * VariableBase::Data() const
{
	return data;
}

void VariableBase::Serialize( std::ostream& os ) const
{
	meta->Serialize( os, RefVariable( meta, data ) );
}

void VariableBase::SetData(void *d)
{
	data = d;
}
