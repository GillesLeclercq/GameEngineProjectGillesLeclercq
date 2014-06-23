#include "CameraManager.h"


using namespace std;
using namespace DirectX;

//-------------------------------------------------------------;---------
// Subscribe to all needed events (Event_DeleteObject ...)
// Return true if successfull
bool CameraManager::VInitialize( GameObjectManager* goManager )
{
	// Event_DeleteObject => OnDestroyGO
	EventManager::Instance().Bind( Event_DeleteObject::EventType(), fastdelegate::MakeDelegate( this, &ICameraManager::OnDestroyGO ) );
	// Event_CreateObject => OnCreateGO
	EventManager::Instance().Bind( Event_CreateObject::EventType(), fastdelegate::MakeDelegate( this, &ICameraManager::OnCreateGO ) );

	EventManager::Instance().Bind( Event_NewCurrentCamera::EventType(), fastdelegate::MakeDelegate( this, &CameraManager::SetNewCurrentCamera ) );

	goManager->RegisterComponentCreator( "Camera", Camera::CreateComponent );

	return true;
}

//----------------------------------------------------------------------
void CameraManager::SetNewCurrentCamera(IEventPtr evt)
{
	shared_ptr<Event_NewCurrentCamera> newCurrentCameraEvt = static_pointer_cast<Event_NewCurrentCamera>(evt);
	if ( m_pCurrentCamera == nullptr )
	{
		m_pCurrentCamera = newCurrentCameraEvt->GetCamera();
	}
	else
	{
		m_pCurrentCamera->SetCurrentCamera(false);
		m_pCurrentCamera = m_pCameras.find(newCurrentCameraEvt->GetGameObjectId())->second;
		m_pCurrentCamera->SetCurrentCamera(true);
	}
}