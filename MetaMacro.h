#pragma once

#define META_TYPE( TYPE ) (MetaCreator<RemQual<TYPE>::type>::Get( ))
#define META( OBJECT ) (MetaCreator<RemQual<decltype( OBJECT )>::type>::Get( ))
#define META_STR( STRING ) (MetaManager::Get( STRING ))

#define PASTE( _, __ )  _##__
#define NAME_GENERATOR_INTERNAL( _ ) PASTE( GENERATED_NAME, _ )
#define NAME_GENERATOR( ) NAME_GENERATOR_INTERNAL( __COUNTER__ )

// 클래스 멤버를 추가하기 위한 매크로
#define DEFINE_META( TYPE ) \
	MetaCreator<RemQual<TYPE>::type> NAME_GENERATOR( )( #TYPE, sizeof( TYPE ) ); \
	RemQual<TYPE>::type *TYPE::NullCast() { return reinterpret_cast<RemQual<TYPE>::type *>(NULL); } \
	void TYPE::AddMember( std::string name, unsigned offset, MetaData *data ) { return MetaCreator<RemQual<TYPE>::type>::AddMember( name, offset, data ); } \
	void MetaCreator<RemQual<TYPE>::type>::RegisterMetaData( void ) { TYPE::RegisterMetaData(); } \
	void TYPE::RegisterMetaData()

#define META_DATA( TYPE ) \
	static RemQual<TYPE>::type *NullCast(); \
	static void AddMember( std::string name, unsigned offset, MetaData *data ); \
	static void RegisterMetaData();

// POD 타입 추가를 위한 매크로
#define DEFINE_META_POD( TYPE ) \
	MetaCreator<RemQual<TYPE>::type> NAME_GENERATOR( )( #TYPE, sizeof( TYPE ) ); \
	void MetaCreator<RemQual<TYPE>::type>::RegisterMetaData() \
{ \
	MetaCreator<RemQual<TYPE>::type>::SetSerializeFn( TextSerializePrim<RemQual<TYPE>::type> ); \
}

#define ADD_MEMBER( MEMBER ) \
	AddMember( #MEMBER, (unsigned)(&(NullCast()->MEMBER)), META(NullCast()->MEMBER))

#define BIND_FUNCTION( FN ) \
	BuildFunction<decltype( &FN ), &FN>( &FN )

#define REGISTER_FUNC_TO_LUA( L, FN ) \
	static Function FN##Function = BIND_FUNCTION(FN); \
	Lua::BindFunctionToLua(L, &FN##Function, #FN)

#define REGISTER_FUNC_TO_LUA_WITH_NAME( L, FN, NAME ) \
	static Function NAME##Function = BIND_FUNCTION( FN ); \
	Lua::BindFunctionToLua( L, &NAME##Function, #NAME )

#define SET_TO_LUA(T, CB) \
	((MetaData *)META_TYPE(T))->SetToLua(CB)

#define SET_FROM_LUA(T, CB) \
	((MetaData *)META_TYPE(T))->SetFromLua(CB)
