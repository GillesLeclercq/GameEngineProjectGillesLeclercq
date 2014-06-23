#include "ITransfoManager.h"

using namespace std;

//----------------------------------------------------------------------
// Add a new component to the map
// Return true if successfull
bool ITransfoManager::RegisterGameObject( GameObject* newGO )
{
	if( m_pTransformations.find( newGO->GetID() ) == m_pTransformations.end() )
	{
		IComponent* TransfoComp = newGO->GetComponent( Transformation::GetComponentType() );
		if( TransfoComp )
		{
			m_pTransformations[ newGO->GetID() ] = dynamic_cast<Transformation*>( TransfoComp );
			return true;
		}
	}
	return false;
}

ITransfoManager::~ITransfoManager()
{

}

//----------------------------------------------------------------------
// DELEGATES
//----------------------------------------------------------------------
// Remove the component corresponding to the deleted GO if it exists
void ITransfoManager::OnCreateGO( IEventPtr evt )
{
	shared_ptr<Event_CreateObject> createEvt = static_pointer_cast<Event_CreateObject>(evt);
	RegisterGameObject( createEvt->GetNewGameObject() );
}

//----------------------------------------------------------------------
// Remove the component corresponding to the deleted GO if it exists
void ITransfoManager::OnDestroyGO( IEventPtr evt )
{
	shared_ptr<Event_DeleteObject> deleteEvt = static_pointer_cast<Event_DeleteObject>(evt);
	m_pTransformations.erase( deleteEvt->GetDeletedID() );
}