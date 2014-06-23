#include "MeshManager.h"

using namespace std;
using namespace DirectX;

//----------------------------------------------------------------------
// Subscribe to all needed events (Event_DeleteObject ...)
// Return true if successfull
bool MeshManager::VInitialize( GameObjectManager* goManager )
{
	// Event_DeleteObject => OnDestroyGO
	EventManager::Instance().Bind( Event_DeleteObject::EventType(), fastdelegate::MakeDelegate( this, &IMeshManager::OnDestroyGO ) );
	// Event_CreateObject => OnCreateGO
	EventManager::Instance().Bind( Event_CreateObject::EventType(), fastdelegate::MakeDelegate( this, &IMeshManager::OnCreateGO ) );

	goManager->RegisterComponentCreator( "Mesh", Mesh::CreateComponent );

	return true;
}

//----------------------------------------------------------------------
