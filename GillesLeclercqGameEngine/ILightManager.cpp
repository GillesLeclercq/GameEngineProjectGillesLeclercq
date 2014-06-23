#include "ILightManager.h"

using namespace std;

//----------------------------------------------------------------------
// Add a new component to the map
// Return true if successfull
bool ILightManager::RegisterGameObject( GameObject* newGO )
{
	if(    m_pDirectionalLights.find( newGO->GetID() ) == m_pDirectionalLights.end() 
		&& m_pPointLights.find( newGO->GetID() ) == m_pPointLights.end())
	{		
		IComponent* LightComp = newGO->GetComponent( DirectionalLightContainer::GetComponentType() );
		if( dynamic_cast<DirectionalLightContainer*>(LightComp) != nullptr )
		{

			m_pDirectionalLights[ newGO->GetID() ] = dynamic_cast<DirectionalLightContainer*>( LightComp );
			return true;
		}

		LightComp = newGO->GetComponent( PointLightContainer::GetComponentType() );
		if( dynamic_cast<PointLightContainer*>(LightComp) != nullptr )
		{
			m_pPointLights[ newGO->GetID() ] = dynamic_cast<PointLightContainer*>( LightComp );
			return true;
		}
	}
	return false;
}

ILightManager::~ILightManager()
{

}

//----------------------------------------------------------------------
// DELEGATES
//----------------------------------------------------------------------
// Remove the component corresponding to the deleted GO if it exists
void ILightManager::OnCreateGO( IEventPtr evt )
{
	shared_ptr<Event_CreateObject> createEvt = static_pointer_cast<Event_CreateObject>(evt);
	RegisterGameObject( createEvt->GetNewGameObject() );
}

//----------------------------------------------------------------------
// Remove the component corresponding to the deleted GO if it exists
void ILightManager::OnDestroyGO( IEventPtr evt )
{
	shared_ptr<Event_DeleteObject> deleteEvt = static_pointer_cast<Event_DeleteObject>(evt);
	m_pDirectionalLights.erase( deleteEvt->GetDeletedID() );
	m_pPointLights.erase( deleteEvt->GetDeletedID() );
}

//-------------------------------------------------------------------
// Return an array of Directional light
vector<DirectionalLight> ILightManager::GetVectorDirectionalLights()
{
	vector<DirectionalLight> vectorDirectionLight;
	if (m_pDirectionalLights.size() == 0)
	{
		return vectorDirectionLight;
	}
	for (auto it : m_pDirectionalLights)
	{
		vectorDirectionLight.push_back(*it.second->GetDirectionalLight());
	}
	return vectorDirectionLight;
}

//-------------------------------------------------------------------
// Return an array of Point light
vector<PointLight> ILightManager::GetVectorPointLights()
{
	vector<PointLight> vectorPointLight;
	if (m_pPointLights.size() == 0)
	{
		return vectorPointLight;
	}
	for (auto it : m_pPointLights)
	{
		vectorPointLight.push_back(*it.second->GetPointLight());
	}
	return vectorPointLight;
}
