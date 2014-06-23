#include "LuaStateManager.h"

using namespace std;

bool LuaStateManager::VInitialize()
{
	m_pLuaState = lua_open();
	luaL_openlibs( m_pLuaState );
	return true;
}

bool LuaStateManager::VExecuteFile( const char* file )
{
	int error = 0;
	error = luaL_loadfile(m_pLuaState, file);
	if( error != 0 )
	{
		std::cerr << "[LUA] ERROR " << error << ": " << file << " cannot be loaded." << std::endl;
		return error;
	}
	error = lua_pcall(m_pLuaState, 0, LUA_MULTRET, 0);
	if( error != 0 )
	{
		std::cerr << "[LUA] ERROR " << error << ": " << file << " cannot be executed." << std::endl;
		return false;
	}
	return true;
}

bool LuaStateManager::VExecuteString( const char* cmd )
{
	int error = luaL_dostring( m_pLuaState, cmd );
	if( error != 0 )
	{
		std::cerr << "[LUA] ERROR " << error << ": Command \"" << cmd << "\" cannot be executed." << std::endl;
		return false;
	}
	return true;
}

//bool LuaStateManager::CreateNewTable( const char* Name )
//{
//	bool result = true;
//	vector<string> pathSteps = StringUtilities::Split( Name, '.' );
//	int pathLength = pathSteps.size();
//	int push = 0;
//
//	lua_settop( m_pLuaState, 0 );
//
//	if( pathLength > 1 )
//	{
//		lua_getglobal( m_pLuaState, pathSteps.at(0).c_str() );
//		push++;
//
//		for( int i = 1; i<pathSteps.size()-1 && result; i++ )
//		{
//			if( CheckTopTypeTable() )
//			{
//				lua_getfield( m_pLuaState, -2, pathSteps.at(i).c_str() );
//				push++;
//			}
//			else
//			{
//				result = false;
//			}
//		}
//
//		if( !CheckTopTypeTable() )
//		{
//			result = false;
//		}
//	}
//
//	if( result )
//	{
//		lua_newtable( m_pLuaState );
//		lua_setfield( m_pLuaState, ( pathLength>1 ? -2 : LUA_GLOBALSINDEX ), pathSteps.end()->c_str() );
//	}
//	else
//	{
//		 cerr << "[LUA] ERROR: Table cannot be created at " << Name << endl;
//	}
//
//	lua_pop( m_pLuaState, push );
//	return result;
//}

template <> void LuaStateManager::PushOnStack<int>( int newValue ) { return lua_pushinteger( m_pLuaState, newValue ); }
template <> void LuaStateManager::PushOnStack<float>( float newValue ) { return lua_pushnumber( m_pLuaState, newValue ); }
template <> void LuaStateManager::PushOnStack<const char*>( const char* newValue ) { return lua_pushstring( m_pLuaState, newValue ); }
template <> void LuaStateManager::PushOnStack<bool>( bool newValue ) { return lua_pushboolean( m_pLuaState, newValue ); }

template<> int LuaStateManager::GetStackVariableFromTop<int>( unsigned int i ) const { return lua_tointeger( m_pLuaState, (-1)*i ); }
template<> float LuaStateManager::GetStackVariableFromTop<float>( unsigned int i ) const { return lua_tonumber( m_pLuaState, (-1)*i ); }
template<> const char* LuaStateManager::GetStackVariableFromTop<const char*>( unsigned int i ) const { return lua_tostring( m_pLuaState, (-1)*i ); }
template<> bool LuaStateManager::GetStackVariableFromTop<bool>( unsigned int i ) const { return lua_toboolean( m_pLuaState, (-1)*i ); }
template<> void* LuaStateManager::GetStackVariableFromTop<void*>( unsigned int i ) const { return lua_touserdata( m_pLuaState, (-1)*i ); }

template<> int LuaStateManager::GetStackVariableFromBottom<int>( unsigned int i ) const { return lua_tointeger( m_pLuaState, i ); }
template<> float LuaStateManager::GetStackVariableFromBottom<float>( unsigned int i ) const { return lua_tonumber( m_pLuaState, i ); }
template<> const char* LuaStateManager::GetStackVariableFromBottom<const char*>( unsigned int i ) const { return lua_tostring( m_pLuaState, i ); }
template<> bool LuaStateManager::GetStackVariableFromBottom<bool>( unsigned int i ) const { return lua_toboolean( m_pLuaState, i ); }
template<> void* LuaStateManager::GetStackVariableFromBottom<void*>( unsigned int i ) const { return lua_touserdata( m_pLuaState, i ); }


template <> bool LuaStateManager::CheckStackTypeFromTop<int>( unsigned int i ) const { return lua_isnumber( m_pLuaState, (-1)*i ) == 1; }
template <> bool LuaStateManager::CheckStackTypeFromTop<float>( unsigned int i ) const { return lua_isnumber( m_pLuaState, (-1)*i ) == 1; }
template <> bool LuaStateManager::CheckStackTypeFromTop<const char*>( unsigned int i ) const { return lua_isstring( m_pLuaState, (-1)*i ) == 1; }
template <> bool LuaStateManager::CheckStackTypeFromTop<bool>( unsigned int i ) const { return lua_isboolean( m_pLuaState, (-1)*i ) == 1; }
template <> bool LuaStateManager::CheckStackTypeFromTop<void*>( unsigned int i ) const { return lua_isuserdata( m_pLuaState, (-1)*i ) == 1; }

template <> bool LuaStateManager::CheckStackTypeFromBottom<int>( unsigned int i ) const { return lua_isnumber( m_pLuaState, i ) == 1; }
template <> bool LuaStateManager::CheckStackTypeFromBottom<float>( unsigned int i ) const { return lua_isnumber( m_pLuaState, i ) == 1; }
template <> bool LuaStateManager::CheckStackTypeFromBottom<const char*>( unsigned int i ) const { return lua_isstring( m_pLuaState, i ) == 1; }
template <> bool LuaStateManager::CheckStackTypeFromBottom<bool>( unsigned int i ) const { return lua_isboolean( m_pLuaState, i ) == 1; }
template <> bool LuaStateManager::CheckStackTypeFromBottom<void*>( unsigned int i ) const { return lua_isuserdata( m_pLuaState, i ) == 1; }