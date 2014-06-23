#include "LuaAi.h"
#include <iostream>

bool LuaAi::VInitialize( GameObjectManager* pGOManager )
{	
	bool result = true;

	result &= pGOManager->RegisterComponentCreator( "BasicScriptComponent", BasicScriptComponent::CreateComponent );
	result &= pGOManager->RegisterComponentCreator( "TestComponent", TestComponent::CreateComponent );

	LuaStateManager::Instance().RegisterFunction( "GetGOVariable", BasicScriptComponent::GetGOVariable );
	LuaStateManager::Instance().RegisterFunction( "SetGOVariable", BasicScriptComponent::SetGOVariable );
	LuaStateManager::Instance().RegisterFunction( "GetGOExtVariable", BasicScriptComponent::GetGOExtVariable );

	m_Initialized = LuaStateManager::Instance().VExecuteFile( ".\\Scripts\\InitClass.lua" );

	return m_Initialized;
}