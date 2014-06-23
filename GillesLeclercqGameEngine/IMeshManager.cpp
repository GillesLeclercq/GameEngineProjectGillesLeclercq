#include "IMeshManager.h"

using namespace std;

//----------------------------------------------------------------------
// Add a new component to the map
// Return true if successfull
bool IMeshManager::RegisterGameObject( GameObject* newGO )
{
	if( m_pMesh.find( newGO->GetID() ) == m_pMesh.end() )
	{
		IComponent* MeshComp = newGO->GetComponent( Mesh::GetComponentType() );
		if( MeshComp )
		{
			m_pMesh[ newGO->GetID() ] = dynamic_cast<Mesh*>( MeshComp );
			return true;
		}
	}
	return false;
}

IMeshManager::~IMeshManager()
{
	for (auto m : m_pMesh)
	{
		//SAFE_DELETE(m.second);
	}
}

//----------------------------------------------------------------------
// DELEGATES
//----------------------------------------------------------------------
// Remove the component corresponding to the deleted GO if it exists
void IMeshManager::OnCreateGO( IEventPtr evt )
{
	shared_ptr<Event_CreateObject> createEvt = static_pointer_cast<Event_CreateObject>(evt);
	RegisterGameObject( createEvt->GetNewGameObject() );
}

//----------------------------------------------------------------------
// Remove the component corresponding to the deleted GO if it exists
void IMeshManager::OnDestroyGO( IEventPtr evt )
{
	shared_ptr<Event_DeleteObject> deleteEvt = static_pointer_cast<Event_DeleteObject>(evt);
	m_pMesh.erase( deleteEvt->GetDeletedID() );
}