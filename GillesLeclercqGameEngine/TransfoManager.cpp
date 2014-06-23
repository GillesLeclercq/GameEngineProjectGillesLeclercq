#include "TransfoManager.h"

#include <string>
using namespace std;
using namespace DirectX;

//----------------------------------------------------------------------
// Subscribe to all needed events (Event_DeleteObject ...)
// Return true if successfull
bool TransfoManager::VInitialize( GameObjectManager* goManager )
{
	// Event_DeleteObject => OnDestroyGO
	EventManager::Instance().Bind( Event_DeleteObject::EventType(), fastdelegate::MakeDelegate( this, &ITransfoManager::OnDestroyGO ) );
	// Event_CreateObject => OnCreateGO
	EventManager::Instance().Bind( Event_CreateObject::EventType(), fastdelegate::MakeDelegate( this, &ITransfoManager::OnCreateGO ) );

	goManager->RegisterComponentCreator( "Transformation", Transformation::CreateComponent );

	return true;
}

//----------------------------------------------------------------------
