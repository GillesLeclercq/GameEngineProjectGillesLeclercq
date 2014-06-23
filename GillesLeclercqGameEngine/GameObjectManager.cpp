#include "GameObjectManager.h"

//----------------------------------------------------------------------
GameObjectManager::~GameObjectManager() 
{ 
	for( auto o : m_pObjects ) 
		SAFE_DELETE( o.second );  
}

//----------------------------------------------------------------------
// Call the factory to create new GameObject as described in the file
// Send a Event_CreateObject
void GameObjectManager::LoadGameObjects( const char* file )
{
	XmlMediator* pRoot = TinyXmlLoader::Instance().LoadFile( file );

	if( pRoot == nullptr )
	{
		std::cerr << "[GOManager] Loading objects from " << file << " failed." << std::endl;
		return;
	}

	auto pGOChildren = pRoot->GetChildren( std::string("GameObject") );
	for( auto It = pGOChildren.begin(); It != pGOChildren.end(); It++ )
	{
		GameObject* newGO = m_pGOFactory->CreateGameObject( *It );

		if( newGO != nullptr )
		{
			m_pObjects[ newGO->GetID() ] = newGO;
			EventManager::Instance().SendEvent( std::make_shared<Event_CreateObject>( Event_CreateObject( newGO ) ) );
		}
		else
		{
			std::cerr << "[GOManager] Error in GameObject load." << std::endl;
		}
	}

	SAFE_DELETE( pRoot );
}

//----------------------------------------------------------------------
void GameObjectManager::Update( float& frameTime ) 
{ 
	for( auto o : m_pObjects ) 
		o.second->Update( frameTime ); 
}