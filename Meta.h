#pragma once

class Variable;
class RefVariable;
class MetaData;

typedef void (*SerializeFn)( std::ostream&, RefVariable );
typedef void (*ToLuaCB)(lua_State *, Variable&);
typedef void (*FromLuaCB)(lua_State *, int, Variable *);

class Member
{
public:
	Member(std::string string, unsigned val, MetaData *meta)
		:name(string), offset(val), data(meta), next(NULL) {}
	~Member() {}

	const std::string &Name() const { return name; }
	unsigned Offset() const { return offset; }
	const MetaData *Meta() const { return data; }
	Member *& Next() { return next; }
	const Member *const& Next() const { return next; }

private:
	std::string name;
	unsigned offset;
	const MetaData *data;
	Member *next;
};

class MetaData 
{
public:
	MetaData( std::string string = "", unsigned val = 0 );
	~MetaData() {}

	void Init(std::string& string, unsigned val);
	void AddMember( const Member * member);
	void PrintMembers( std::ostream& os );
	bool HasMembers( void ) const;
	
	void Copy( void *dest, const void *src ) const;
	void Delete( void *data ) const;
	void *NewCopy( const void *src ) const;
	void *New( void ) const;

	const Member *Members() const;
	const std::string& Name() const;
	unsigned Size() const;

	void SetSerialize( SerializeFn fn = NULL );
	void Serialize( std::ostream& os, RefVariable& ) const;  
	void SetToLua(ToLuaCB cb);
	void SetFromLua(FromLuaCB cb);

	void ToLua(lua_State *L, Variable var) const;
	void FromLua(lua_State *L, int index, Variable *var) const;
	void(*PlacementNew)(void *data);
	void(*PlacementDelete)(void *data);
	const char *LuaMetaTable(void) const;
	void SetMetaTable(const char *str);

private:
	std::string name;
	unsigned size;
	Member *head;
	Member *tail;
	SerializeFn serialize;
	ToLuaCB m_toLua;
	FromLuaCB m_fromLua;
	const char *m_metatable;
};

template<typename MetaType>
class MetaCreator
{
public:
	MetaCreator(std::string string, unsigned val)
	{
		Init(string, val);
		Get()->PlacementNew = PlacementNew<MetaType>;
		Get()->PlacementDelete = PlacementDelete<MetaType>;
		Get()->SetMetaTable(string.c_str());
	}

	static MetaData *Get()
	{
		static MetaData instance;
		return &instance;
	}

	static void AddMember(std::string memberName, unsigned memberOffset, MetaData *meta)
	{
		Get()->AddMember(new Member(memberName, memberOffset, meta));
	}

	static MetaType *NullCast()
	{
		return reinterpret_cast<MetaType *>(NULL);
	}

	static void SetSerializeFn(SerializeFn fn)
	{
		Get()->SetSerialize(fn);
	}

	static void RegisterMetaData();

private:
	static void Init(std::string& Name, unsigned size)
	{
		Get()->Init(Name, size);
		MetaManager::RegisterMeta(Get());
		RegisterMetaData();
	}
};

class MetaManager
{
	typedef std::map<std::string, MetaData *> MetaMap;
public:
	static void RegisterMeta(MetaData *instance)
	{
		GetMap()[instance->Name()] = instance;
	}

	static MetaData *Get(std::string Name)
	{
		return GetMap()[Name];
	}

	static MetaMap& GetMap()
	{
		static MetaMap map;
		return map;
	}
};

template <typename T>
inline void PlacementNew(void *data)
{
	new (data)T;
}

template <typename T>
inline void PlacementDelete(void *data)
{
	((T *)data)->~T();
}