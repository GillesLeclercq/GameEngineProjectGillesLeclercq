#include "ICameraManager.h"

using namespace std;

//----------------------------------------------------------------------
// Add a new component to the map
// Return true if successfull
bool ICameraManager::RegisterGameObject( GameObject* newGO )
{
	if( m_pCameras.find( newGO->GetID() ) == m_pCameras.end() )
	{
		IComponent* CameraComp = newGO->GetComponent( Camera::GetComponentType() );
		if( CameraComp )
		{
			m_pCameras[ newGO->GetID() ] = dynamic_cast<Camera*>( CameraComp );
			return true;
		}
	}
	return false;
}

ICameraManager::~ICameraManager()
{
	for (auto c : m_pCameras)
	{
		SAFE_DELETE(c.second);
	}
}

//----------------------------------------------------------------------
// DELEGATES
//----------------------------------------------------------------------
// Remove the component corresponding to the deleted GO if it exists
void ICameraManager::OnCreateGO( IEventPtr evt )
{
	shared_ptr<Event_CreateObject> createEvt = static_pointer_cast<Event_CreateObject>(evt);
	RegisterGameObject( createEvt->GetNewGameObject() );
}

//----------------------------------------------------------------------
// Remove the component corresponding to the deleted GO if it exists
void ICameraManager::OnDestroyGO( IEventPtr evt )
{
	shared_ptr<Event_DeleteObject> deleteEvt = static_pointer_cast<Event_DeleteObject>(evt);
	m_pCameras.erase( deleteEvt->GetDeletedID() );
}