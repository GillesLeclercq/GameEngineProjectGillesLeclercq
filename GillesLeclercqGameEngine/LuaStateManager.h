#pragma once

#include <iostream>
#include "Lua/lua.hpp"

#include "IScriptManager.h"
#include "Utilities.h"

class LuaStateManager : public IScriptManager
{
private:
	lua_State* m_pLuaState;

	template <typename T> bool _GetGlobalVariable( T& globalOut, const char* key );
	template <typename T> bool _GetGlobalTableValue( T& globalOut, std::vector<std::string>& key, unsigned int index );

public:
	virtual bool VInitialize() override;
	virtual bool VExecuteFile( const char* file ) override;
	virtual bool VExecuteString( const char* cmd ) override;

	void RegisterFunction( const char* luaName, lua_CFunction func ) { lua_register( m_pLuaState, luaName, func ); }

	lua_State* GetLuaState() const { return m_pLuaState; }

	template <typename T> bool GetGlobal( T& globalOut, const char* key, unsigned int index = 0 );

	int GetStackSize() const { return lua_gettop( m_pLuaState ); }

	template <typename T> void PushOnStack( T newValue );

	// Variables accessors
	template <typename T> T GetStackVariableFromTop( unsigned int i ) const;
	template <typename T> T GetStackVariableFromBottom( unsigned int i ) const;

	template <typename T> T GetTopVariable() const { return GetStackVariableFromTop<T>( 1 ); }

	// Type checking
	template <typename T> bool CheckStackTypeFromTop( unsigned int i ) const;
	bool CheckStackTypeFromTopTable( unsigned int i ) const { return lua_istable( m_pLuaState, (-1)*i ); }

	template <typename T> bool CheckStackTypeFromBottom( unsigned int i ) const;
	bool CheckStackTypeFromBottomTable( unsigned int i ) const { return lua_istable( m_pLuaState, i ); }

	template <typename T> bool CheckTopType() const { return CheckStackTypeFromTop<T>( 1 ); }
	bool CheckTopTypeTable() const { return CheckStackTypeFromBottomTable( 1 ); }

	static LuaStateManager& Instance() 
	{ 
		static LuaStateManager instance;
		return instance;
	}

// Singleton
private:
	LuaStateManager( const LuaStateManager& )					{}
	LuaStateManager& operator=( const LuaStateManager& )		{}

	LuaStateManager()											{ VInitialize(); }
	~LuaStateManager()											{ lua_close( m_pLuaState ); m_pLuaState = nullptr; }
};

template <typename T> bool LuaStateManager::_GetGlobalVariable( T& globalOut, const char* key )
{
	bool result;

	lua_settop( m_pLuaState, 0 );
	lua_getglobal( m_pLuaState, key );

	result = CheckTopType<T>();
	if( result )
	{
		globalOut = GetTopVariable<T>();
	}

	lua_pop( m_pLuaState, -1 );

	return result;
}

template <typename T> bool LuaStateManager::_GetGlobalTableValue( T& globalOut, std::vector<std::string>& key, unsigned int index )
{
	bool result = true;
	int pushes = 0;

	lua_settop( m_pLuaState, 0 );
	lua_getglobal( m_pLuaState, key.at(0).c_str() );
	pushes++;

	unsigned int pathLength = key.size();

	for( unsigned int i = 1; i < pathLength && result; i++ )
	{
		if( CheckTopTypeTable() )
		{
			PushOnStack( key.at( i ).c_str() );
			lua_gettable( m_pLuaState, -2 );
			pushes++;
		}
		else
		{
			result = false;
		}
	}

	if( result )
	{
		if( index != 0 && CheckTopTypeTable() )
		{
			PushOnStack( (int)index );
			lua_gettable( m_pLuaState, -2 );
			pushes++;
		}

		if( CheckTopType<T>() )
		{
			globalOut = GetTopVariable<T>();
		}
		else
		{
			result = false;
		}
	}

	lua_pop( m_pLuaState, pushes );
	return result;
	
}

template <typename T> bool LuaStateManager::GetGlobal( T& globalOut, const char* key, unsigned int index )
{
	bool result = false;

	std::vector<std::string> Tables = StringUtilities::Split( key, '.');
	if( Tables.size() == 1 && index == 0 ) // Global variable
	{
		if( _GetGlobalVariable( globalOut, key ) )
		{
			std::cerr << "[LUA] ERROR: Incorrect variable: " << key << "." << std::endl;
			return false;
		}
		return true;
	}
	else // Table value
	{
		if( !_GetGlobalTableValue( globalOut, Tables, index ) )
		{
			std::cerr << "[LUA] ERROR: Incorrect path: " << key << "[" << index << "]." << std::endl;
			return false;
		}
		return true;
	}
}