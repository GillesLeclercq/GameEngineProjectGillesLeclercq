#pragma once

#include <map>
#include <set>
#include <string>
#include <memory>
#include "FastDelegate/FastDelegate.h"

#include "EventManager.h"
#include "Event_AttributeRequest.h"
#include "Event_AttributeDelivery.h"
#include "Utilities.h"

typedef fastdelegate::FastDelegate1<float&> UpdateMethod;
typedef fastdelegate::FastDelegate1<void*> SetMethod;
typedef fastdelegate::FastDelegate0<void*> GetMethod;

class IComponent;

class GameObject
{
private:
	int m_ID;

	std::map<unsigned long, IComponent*>			m_pComponents;
	std::map<unsigned long, UpdateMethod>			m_UpdateMethods;

	std::map<std::string, std::set<SetMethod>>		m_SetMethods;
	std::map<std::string, GetMethod>				m_GetMethods;

	void* m_pTempExternalAttribute;

public:
	GameObject( int& id ): m_ID( id ), m_pTempExternalAttribute( nullptr ) {}
	~GameObject();

	void Init();

	bool AddComponent( const unsigned long& compID, IComponent* newComponent );
	bool RemoveComponent( const unsigned long& compID );

	void* GetVariable( std::string key );
	void SetVariable( std::string key, void* newValue );

	void* GetExternalAttribute( std::string key, int receiver );

	void RegisterUpdateMethod( const unsigned long& compID, UpdateMethod newUpdate ) { m_UpdateMethods[ compID ] = newUpdate; }
	void UnRegisterUpdateMethod( const unsigned long& compID ) { m_UpdateMethods.erase(compID); }

	bool RegisterGetMethod( std::string key, GetMethod method );
	void UnRegisterGetMethod( std::string key ) { m_GetMethods.erase( StringUtilities::ToLower(key) ); }
	void RegisterSetMethod( std::string key, SetMethod method );
	void UnRegisterSetMethod( std::string key, SetMethod method );
	
	void OnAttributeDelivery( IEventPtr pAttDelivery );
	void OnAttributeRequest( IEventPtr pAttRequest );
	void SendAttributeRequest( int receiver, std::string attID );

	IComponent* GetComponent( const unsigned long& compID ) const;

	void Update( float& frameTime );

	int GetID() const { return m_ID; }
};