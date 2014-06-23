#pragma once

#include <string>
#include <vector>
#include "Lua\lua.hpp"

#include "IScriptComponent.h"
#include "LuaStateManager.h"

class BasicScriptComponent : public IScriptComponent
{
private:
	static const unsigned long s_CompType = 0xcad061a7;

	std::string m_LuaClassName;
	std::string m_LuaInstanceName;
	std::string m_LuaUpdateMethodName;

	static BasicScriptComponent* s_pCurrentInstance;

public:
	BasicScriptComponent( GameObject* pOwner ): IScriptComponent( pOwner ), 
		m_LuaClassName( "" ), m_LuaInstanceName( "" ), m_LuaUpdateMethodName( "" ) {}
	~BasicScriptComponent();

	virtual bool VInitialize( XmlMediator* pComponent );

	void Update( float& frameTime );

	static IComponent* CreateComponent( GameObject* owner ) { return new BasicScriptComponent( owner ); }

	virtual const unsigned long& VGetComponentType() const { return s_CompType; }
	static const unsigned long& GetComponentType() { return s_CompType; }

	// Lua-reserved method
	static int GetGOVariable( lua_State* pLuaState );
	static int SetGOVariable( lua_State* pLuaState );
	static int GetGOExtVariable( lua_State* pLuaState );
};