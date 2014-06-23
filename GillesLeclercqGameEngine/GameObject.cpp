#include "GameObject.h"
#include "IComponent.h"

//----------------------------------------------------------------------
GameObject::~GameObject()
{ 
	for( auto c : m_pComponents ) 
	{
		SAFE_DELETE( c.second );
	}
}

//----------------------------------------------------------------------
void GameObject::Init() 
{
	EventManager::Instance().Bind( Event_AttributeRequest::EventType(), fastdelegate::MakeDelegate( this, &GameObject::OnAttributeRequest ) );
	EventManager::Instance().Bind( Event_AttributeDelivery::EventType(), fastdelegate::MakeDelegate( this, &GameObject::OnAttributeDelivery ) );
}

//----------------------------------------------------------------------
bool GameObject::AddComponent( const unsigned long& compID, IComponent* newComponent ) 
{ 
	if( m_pComponents.find( compID ) == m_pComponents.end() )
	{
		m_pComponents[ compID ] = newComponent;
		return true;
	}
	return false;
}

//----------------------------------------------------------------------
bool GameObject::RemoveComponent( const unsigned long& compID )
{
	if( m_pComponents.find( compID ) != m_pComponents.end() )
	{
		m_pComponents.erase( compID );
		if( m_UpdateMethods.find( compID ) != m_UpdateMethods.end() )
		{
			m_UpdateMethods.erase( compID );
		}
		return true;
	}
	return false;
}

//----------------------------------------------------------------------
void* GameObject::GetVariable( std::string key )
{
	std::string lowKey = StringUtilities::ToLower( key );
	auto findIt = m_GetMethods.find( lowKey );
	if( findIt != m_GetMethods.end() )
	{
		return findIt->second();
	}
	return nullptr;
}

//----------------------------------------------------------------------
void GameObject::SetVariable( std::string key, void* newValue )
{
	std::string lowKey = StringUtilities::ToLower( key );
	auto findIt = m_SetMethods.find( lowKey );
	if( findIt != m_SetMethods.end() )
	{
		for( auto it : findIt->second )
		{
			it( newValue );
		}
	}
}

//----------------------------------------------------------------------
// Add entry to m_ExternalAttributes if needed, else simply return the entry.
void* GameObject::GetExternalAttribute( std::string key, int receiver )
{
	SendAttributeRequest( receiver, key );
	return m_pTempExternalAttribute;
}

//----------------------------------------------------------------------
bool GameObject::RegisterGetMethod( std::string key, GetMethod method )
{
	std::string lowKey = StringUtilities::ToLower( key );
	auto findIt = m_GetMethods.find( lowKey );
	if( findIt == m_GetMethods.end() )
	{
		m_GetMethods[ lowKey ] = method;
		return true;
	}
	return false;
}

//----------------------------------------------------------------------
void GameObject::RegisterSetMethod( std::string key, SetMethod method )
{
	std::string lowKey = StringUtilities::ToLower( key );
	m_SetMethods[ lowKey ].insert( method );
}

//----------------------------------------------------------------------
void GameObject::UnRegisterSetMethod( std::string key, SetMethod method )
{
	auto findIt = m_SetMethods.find( StringUtilities::ToLower(key) );
	if( findIt != m_SetMethods.end() )
	{
		findIt->second.erase(method);
	}
}

//----------------------------------------------------------------------
void GameObject::OnAttributeDelivery( IEventPtr pAttDelivery )
{
	std::shared_ptr<Event_AttributeDelivery> msg = std::static_pointer_cast<Event_AttributeDelivery>( pAttDelivery );
	if( msg->GetRequester() == m_ID )
	{
		m_pTempExternalAttribute = msg->GetValue();
	}
}

//----------------------------------------------------------------------
void GameObject::OnAttributeRequest( IEventPtr pAttRequest )
{
	std::shared_ptr<Event_AttributeRequest> msg = std::static_pointer_cast<Event_AttributeRequest>( pAttRequest );
	if( msg->GetReceiver() == m_ID )
	{
		EventManager::Instance().SendEvent( std::make_shared<Event_AttributeDelivery>( 
			msg->GetSender(), GetVariable( msg->GetAttributeID() )
		) );
	}
}

//----------------------------------------------------------------------
void GameObject::SendAttributeRequest( int receiver, std::string attID )
{
	std::string lowAttID = StringUtilities::ToLower( attID );
	EventManager::Instance().SendEvent( std::make_shared<Event_AttributeRequest>( 
		m_ID, receiver, lowAttID 
	) );
}

//----------------------------------------------------------------------
IComponent* GameObject::GetComponent( const unsigned long& compID ) const 
{ 
	auto findIt = m_pComponents.find( compID );
	if( findIt == m_pComponents.end() )
	{
		return nullptr;
	}
	return findIt->second; 
}

//----------------------------------------------------------------------
void GameObject::Update( float& frameTime ) 
{ 
	for( auto it : m_UpdateMethods )
	{
		it.second( frameTime );
	}
}