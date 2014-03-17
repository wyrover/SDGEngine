#include "Precompiled.h"

namespace SDGEngine
{
	MetaData::MetaData(std::string string, unsigned val)
		:name(string), size(val), head(NULL), tail(NULL), m_toLua(NULL), m_fromLua(NULL), m_metatable(NULL)
	{
	}

	void MetaData::Init(std::string& string, unsigned val)
	{
		name = string;
		size = val;
	}

	void MetaData::AddMember(const Member * member)
	{
		if (NULL == head)
			head = const_cast<Member *>(member);
		else
			tail->Next() = const_cast<Member *>(member);

		tail = const_cast<Member *>(member);
	}

	void MetaData::PrintMembers(std::ostream& os)
	{
		const Member *mem = head;
		os << "class " << name << std::endl;
		std::cout << "{" << std::endl;
		while (mem) {
			os << "  " << mem->Meta()->Name() << " " << mem->Name() << std::endl;
			mem = mem->Next();
		}
		std::cout << "}" << std::endl;
	}

	const Member * MetaData::Members() const
	{
		return head;
	}

	const std::string& MetaData::Name() const
	{
		return name;
	}

	unsigned MetaData::Size() const
	{
		return size;
	}

	void MetaData::Copy(void *dest, const void *src) const
	{
		memcpy(dest, src, sizeof(size));
	}

	void MetaData::Delete(void *data) const
	{
		delete[] reinterpret_cast<char *>(data);
		data = NULL;
	}

	void * MetaData::NewCopy(const void *src) const
	{
		void *data = new char[size];
		memcpy(data, src, size);
		return data;
	}

	void * MetaData::New(void) const
	{
		return new char[size];
	}

	void MetaData::SetSerialize(SerializeFn fn)
	{
		serialize = fn;
	}

	void MetaData::Serialize(std::ostream& os, RefVariable& var) const
	{
		if (serialize)
			serialize(os, var);
		else
			TextSerialize(os, var);
	}

	bool MetaData::HasMembers(void) const
	{
		return (head) ? true : false;
	}

	void MetaData::ToLua(lua_State *L, Variable var) const
	{
		if (m_toLua)
			m_toLua(L, var);
		else
			Lua::GenericToLua(L, var);
	}

	void MetaData::FromLua(lua_State *L, int index, Variable *var) const
	{
		if (m_fromLua)
			m_fromLua(L, index, var);
		else
			Lua::GenericFromLua(L, index, var);
	}

	const char *MetaData::LuaMetaTable(void) const
	{
		return m_metatable;
	}

	void MetaData::SetToLua(ToLuaCB cb)
	{
		m_toLua = cb;
	}

	void MetaData::SetFromLua(FromLuaCB cb)
	{
		m_fromLua = cb;
	}

	void MetaData::SetMetaTable(const char *str)
	{
		m_metatable = str;
	}
}
