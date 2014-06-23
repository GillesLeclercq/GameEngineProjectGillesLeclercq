#pragma once

#include <iostream>
#include <map>
#include <memory>

#include "TinyXmlLoader.h"

#include "GameObjectFactory.h"

#include "GameObject.h"
#include "IComponent.h"

#include "EventManager.h"
#include "Event_CreateObject.h"
#include "Event_DeleteObject.h"

class GameObjectManager
{
private:
	GameObjectFactory*			m_pGOFactory;

	std::map<int, GameObject*>	m_pObjects;

public:
	GameObjectManager( GameObjectFactory* goFactory ) { m_pGOFactory = goFactory;}
	~GameObjectManager();

	void LoadGameObjects( const char* file );

	void Update( float& frameTime );

	bool RegisterComponentCreator( std::string creatorName, ComponentCreator* creator )		{ return m_pGOFactory->RegisterComponentCreator( creatorName, creator ); }
};