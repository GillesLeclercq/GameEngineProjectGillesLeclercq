#include "BasicScriptComponent.h"

#include "GameObject.h"

#include <iostream>

using namespace std;

BasicScriptComponent* BasicScriptComponent::s_pCurrentInstance = nullptr;

//----------------------------------------------------------------------
BasicScriptComponent::~BasicScriptComponent()
{
	m_pOwner->UnRegisterUpdateMethod( s_CompType );
}

//----------------------------------------------------------------------
bool BasicScriptComponent::VInitialize( XmlMediator* pComponent )
{
	s_pCurrentInstance = this;

	string fileName = "";

	auto AllChildren = pComponent->GetAllChildren();
	for( auto scriptInfo = AllChildren.begin(); scriptInfo != AllChildren.end(); scriptInfo++ )
	{
		if( scriptInfo->first == "File" )
		{
			auto fileNode = scriptInfo->second;
			fileName = scriptInfo->second.front()->GetContent();
			vector<string> elts = StringUtilities::Split( fileName, '\\' );
			m_LuaClassName = StringUtilities::Split( elts.back(), '.' ).front();
			m_LuaInstanceName = m_LuaClassName + to_string( m_pOwner->GetID() );
		}
		else if( scriptInfo->first == "Update" )
		{
			m_LuaUpdateMethodName = scriptInfo->second.front()->GetContent();
		}
	}

	if( fileName == "" || !LuaStateManager::Instance().VExecuteFile( fileName.c_str() ) )
	{
		return false;
	}

	string luaInstr = m_LuaInstanceName + " = " + m_LuaClassName + ":Create( {}, nil )";
	if( !LuaStateManager::Instance().VExecuteString( luaInstr.c_str() ) )
	{
		return false;
	}

	m_pOwner->RegisterUpdateMethod( s_CompType, fastdelegate::MakeDelegate( this, &BasicScriptComponent::Update ) );
	
	s_pCurrentInstance = nullptr;

	return true;
}

//----------------------------------------------------------------------
void BasicScriptComponent::Update( float& frameTime )
{
	s_pCurrentInstance = this;

	string param = to_string( frameTime );
	string cmd = m_LuaInstanceName + ":" + m_LuaUpdateMethodName + "(" + param + ");";

	LuaStateManager::Instance().VExecuteString( cmd.c_str() );

	s_pCurrentInstance = nullptr;
}

//----------------------------------------------------------------------
int BasicScriptComponent::GetGOVariable( lua_State* pLuaState )
{
	if( s_pCurrentInstance == nullptr )
	{
		return 0;
	}

	int ArgsNb = LuaStateManager::Instance().GetStackSize();
	const char* TypeRequested = "";
	const char* Key = "";

	if( ArgsNb != 2 )
	{
		return 0;
	}

	if( LuaStateManager::Instance().CheckStackTypeFromTop<const char*>( 1 ) )
	{
		TypeRequested = LuaStateManager::Instance().GetStackVariableFromTop<const char*>( 1 );
	}
	if( LuaStateManager::Instance().CheckStackTypeFromTop<const char*>( 2 ) )
	{
		Key = LuaStateManager::Instance().GetStackVariableFromTop<const char*>( 2 );
	}
		
	if( TypeRequested == "" || Key == "" )
	{
		return 0;
	}

	void* Result = s_pCurrentInstance->m_pOwner->GetVariable( Key );
	if( Result == nullptr )
	{
		return 0;
	}

	if( strcmp( TypeRequested, "int" ) == 0 )
	{
		LuaStateManager::Instance().PushOnStack( *(int*)Result );
	} 
	else if( strcmp( TypeRequested, "float" ) == 0 )
	{
		LuaStateManager::Instance().PushOnStack( *(float*)Result );
	}
	else if( strcmp( TypeRequested, "string" ) == 0 )
	{
		LuaStateManager::Instance().PushOnStack( (const char*)Result );
	}
	else if( strcmp( TypeRequested, "bool" ) == 0 )
	{
		LuaStateManager::Instance().PushOnStack( *(bool*)Result );
	}
	else 
	{
		return 0;
	}

	return 1;
}

//----------------------------------------------------------------------
int BasicScriptComponent::SetGOVariable( lua_State* pLuaState )
{
	if( s_pCurrentInstance == nullptr )
	{
		return 0;
	}

	int ArgsNb = LuaStateManager::Instance().GetStackSize();
	const char* TypeSent = "";
	void* NewValue = nullptr;
	const char* Key = "";

	if( ArgsNb != 3 )
	{
		return 0;
	}

	if( LuaStateManager::Instance().CheckStackTypeFromTop<const char*>( 1 ) )
	{
		TypeSent = LuaStateManager::Instance().GetStackVariableFromTop<const char*>( 1 );
	}
	if( LuaStateManager::Instance().CheckStackTypeFromTop<const char*>( 3 ) )
	{
		Key = LuaStateManager::Instance().GetStackVariableFromTop<const char*>( 3 );
	}
		
	if( TypeSent == "" || Key == "" )
	{
		return 0;
	}

	if( strcmp( TypeSent, "int" ) == 0 )
	{
		int value = LuaStateManager::Instance().GetStackVariableFromTop<int>( 2 );
		NewValue = &value;
	} 
	else if( strcmp( TypeSent, "float" ) == 0 )
	{
		float value = LuaStateManager::Instance().GetStackVariableFromTop<float>( 2 );
		NewValue = &value;
	}
	else if( strcmp( TypeSent, "string" ) == 0 )
	{
		const char* value = LuaStateManager::Instance().GetStackVariableFromTop<const char*>( 2 );
		NewValue = &value;
	}
	else 
	{
		return 0;
	}

	s_pCurrentInstance->m_pOwner->SetVariable( Key, NewValue );

	return 0;
}

//----------------------------------------------------------------------
int BasicScriptComponent::GetGOExtVariable( lua_State* pLuaState )
{
	if( s_pCurrentInstance == nullptr )
	{
		return 0;
	}

	int ArgsNb = LuaStateManager::Instance().GetStackSize();
	const char* TypeRequested = "";
	const char* Key = "";
	int Receiver = -1;

	if( ArgsNb != 3 )
	{
		return 0;
	}

	if( LuaStateManager::Instance().CheckStackTypeFromTop<const char*>( 1 ) )
	{
		TypeRequested = LuaStateManager::Instance().GetStackVariableFromTop<const char*>( 1 );
	}
	if( LuaStateManager::Instance().CheckStackTypeFromTop<const char*>( 2 ) )
	{
		Key = LuaStateManager::Instance().GetStackVariableFromTop<const char*>( 2 );
	}
	if( LuaStateManager::Instance().CheckStackTypeFromTop<int>( 3 ) )
	{
		Receiver = LuaStateManager::Instance().GetStackVariableFromTop<int>( 3 );
	}
		
	if( TypeRequested == "" || Key == "" || Receiver == -1 )
	{
		return 0;
	}

	void* Result = s_pCurrentInstance->m_pOwner->GetExternalAttribute( Key, Receiver );
	if( Result == nullptr )
	{
		return 0;
	}

	if( strcmp( TypeRequested, "int" ) == 0 )
	{
		LuaStateManager::Instance().PushOnStack( *(int*)Result );
	} 
	else if( strcmp( TypeRequested, "float" ) == 0 )
	{
		LuaStateManager::Instance().PushOnStack( *(float*)Result );
	}
	else if( strcmp( TypeRequested, "string" ) == 0 )
	{
		LuaStateManager::Instance().PushOnStack( (const char*)Result );
	}
	else if( strcmp( TypeRequested, "bool" ) == 0 )
	{
		LuaStateManager::Instance().PushOnStack( *(bool*)Result );
	}
	else 
	{
		return 0;
	}

	int test = LuaStateManager::Instance().GetStackVariableFromTop<int>( 1 );

	return 1;
	
}