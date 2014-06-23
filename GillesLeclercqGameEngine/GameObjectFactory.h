#pragma once

#include <iostream>
#include <map>
#include <list>
#include <string>

#include "GameObject.h"
#include "IComponent.h"

#include "XmlMediator.h"

typedef IComponent* (ComponentCreator)(GameObject*);
typedef std::map<std::string, ComponentCreator*> ComponentCreatorMap;

class GameObjectFactory
{
private:
	std::set<int> m_UsedIDs;
	int m_LastID;

	ComponentCreatorMap m_CompCreatorMap;

	int& NextID();
	bool ReserveID( int& id );

public:
	GameObjectFactory(): m_LastID( -1 )		{}
	~GameObjectFactory()					{}

	GameObject* CreateGameObject( XmlMediator* entityInfo );
	IComponent* CreateComponent( std::string name, GameObject* owner );

	bool RegisterComponentCreator( std::string creatorName, ComponentCreator* creator );
};