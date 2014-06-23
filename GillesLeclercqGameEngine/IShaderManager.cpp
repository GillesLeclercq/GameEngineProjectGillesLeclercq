#include "IShaderManager.h"

using namespace std;

bool IShaderManager::RegisterGameObject( GameObject* newGO )
{
	if( m_pShaders.find( newGO->GetID() ) == m_pShaders.end() )
	{
		IComponent* shaderComp = newGO->GetComponent( Shader::GetComponentType() );
		if( shaderComp )
		{
			m_pShaders[ newGO->GetID() ] = dynamic_cast<Shader*>( shaderComp );
			return true;
		}
	}
	return false;
}

IShaderManager::~IShaderManager()
{
	for (auto s : m_pShaders)
	{
		s.second;
	}
}


void IShaderManager::OnDestroyGO( IEventPtr evt )
{
	shared_ptr<Event_DeleteObject> deleteEvt = static_pointer_cast<Event_DeleteObject>(evt);
	m_pShaders.erase( deleteEvt->GetDeletedID() );
}

void IShaderManager::OnCreateGO( IEventPtr evt )
{
	shared_ptr<Event_CreateObject> createEvt = static_pointer_cast<Event_CreateObject>(evt);
	RegisterGameObject( createEvt->GetNewGameObject() );
}