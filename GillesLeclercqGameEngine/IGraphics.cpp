#include "IGraphics.h"

using namespace std;

//----------------------------------------------------------------------
// Add a new component to the map
// Return true if successfull
bool IGraphics::RegisterGameObject( GameObject* newGO )
{
	if( m_pGraphicComponents.find( newGO->GetID() ) == m_pGraphicComponents.end() )
	{
		IComponent* graphicComp = newGO->GetComponent( GraphicsComponent::GetComponentType() );
		if( graphicComp )
		{
			m_pGraphicComponents[ newGO->GetID() ] = dynamic_cast<GraphicsComponent*>( graphicComp );
			return true;
		}
	}
	return false;
}

//----------------------------------------------------------------------
// DELEGATES
//----------------------------------------------------------------------
// Remove the component corresponding to the deleted GO if it exists
void IGraphics::OnCreateGO( IEventPtr evt )
{
	shared_ptr<Event_CreateObject> createEvt = static_pointer_cast<Event_CreateObject>(evt);
	RegisterGameObject( createEvt->GetNewGameObject() );
}

//----------------------------------------------------------------------
// Remove the component corresponding to the deleted GO if it exists
void IGraphics::OnDestroyGO( IEventPtr evt )
{
	shared_ptr<Event_DeleteObject> deleteEvt = static_pointer_cast<Event_DeleteObject>(evt);
	m_pGraphicComponents.erase( deleteEvt->GetDeletedID() );
}