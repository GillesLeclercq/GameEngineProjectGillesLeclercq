#include "LightManager.h"

using namespace std;
using namespace DirectX;

//----------------------------------------------------------------------
// Subscribe to all needed events (Event_DeleteObject ...)
// Return true if successfull
bool LightManager::VInitialize( GameObjectManager* goManager )
{
	// Event_DeleteObject => OnDestroyGO
	EventManager::Instance().Bind( Event_DeleteObject::EventType(), fastdelegate::MakeDelegate( this, &ILightManager::OnDestroyGO ) );
	// Event_CreateObject => OnCreateGO
	EventManager::Instance().Bind( Event_CreateObject::EventType(), fastdelegate::MakeDelegate( this, &ILightManager::OnCreateGO ) );

	goManager->RegisterComponentCreator( "DirectionalLight", DirectionalLightContainer::CreateComponent );
	goManager->RegisterComponentCreator( "PointLight", PointLightContainer::CreateComponent );
	return true;
}

//----------------------------------------------------------------------
