#include "GameObjectFactory.h"

//----------------------------------------------------------------------------
GameObject* GameObjectFactory::CreateGameObject( XmlMediator* pGOInfo )
{
	if( pGOInfo == nullptr )
	{
		std::cerr << "[GOFactory] GameObject information incorrect." << std::endl;
		return nullptr;
	}

	int ID = -1;
	std::list<XmlMediator*> IDInfo = pGOInfo->GetChildren( std::string("ID") );
	if( !IDInfo.empty() )
	{
		ID = atoi( IDInfo.front()->GetContent().c_str() );
		pGOInfo->DeleteChildren( "ID" );
		if( !ReserveID( ID ) )
		{
			std::cerr << "[GOFactory] ID n°" + std::to_string(ID) + " not valid." << std::endl;
			return nullptr;
		}
	}
	else
	{
		ID = NextID();
	}
	
	GameObject* newGO = new GameObject( ID );

	auto AllChildren = pGOInfo->GetAllChildren();
	for( auto compInfo = AllChildren.begin(); compInfo != AllChildren.end(); compInfo++ )
	{
		if( compInfo->second.size() > 1 )
		{
			std::cerr << "[GOFactory] Several " << compInfo->first << " components detected for GO " << newGO->GetID() << std::endl;
			SAFE_DELETE( newGO );
			break;
		}
		
		IComponent* newComp = CreateComponent( compInfo->first, newGO );

		if( newComp != nullptr && newComp->VInitialize( *(compInfo->second.begin()) ) )
		{
			newGO->AddComponent( newComp->VGetComponentType(), newComp );
		}
		else
		{
			std::cerr << "[GOFactory] Fail to initialize component " << compInfo->first << " for GO " << newGO->GetID() << std::endl;
			SAFE_DELETE( newGO );
			SAFE_DELETE( newComp );
			break;
		} 		
	}

	if( newGO )
	{
		newGO->Init();
	}

	return newGO;
}

//----------------------------------------------------------------------------
IComponent* GameObjectFactory::CreateComponent( std::string name, GameObject* owner )
{
	auto findIt = m_CompCreatorMap.find( name );
	if( findIt == m_CompCreatorMap.end() )
	{
		std::cerr << "[GOFactory] Failed to create " + name + " component." << std::endl;
		return nullptr;
	}

	return m_CompCreatorMap.at( name )( owner );
}

//----------------------------------------------------------------------------
bool GameObjectFactory::RegisterComponentCreator( std::string creatorName, ComponentCreator* creator )
{
	auto findIt = m_CompCreatorMap.find( creatorName );
	if( findIt != m_CompCreatorMap.end() )
	{
		std::cerr << "[GOFactory] " + creatorName + " already exists. Fail to register it in GameObjectFactory." << std::endl;
		return false;
	}

	m_CompCreatorMap[ creatorName ] = creator;
	return true;
}

//----------------------------------------------------------------------------
// Returns the next available ID.
int& GameObjectFactory::NextID() 
{
	do 
	{ 
		m_LastID++; 
	} 
	while( m_UsedIDs.find( m_LastID ) != m_UsedIDs.end() );

	m_UsedIDs.insert( m_LastID );
	return m_LastID;
}

//----------------------------------------------------------------------------
// Add the ID in m_UsedIDs. Returns true if the ID has not been given previously.
bool GameObjectFactory::ReserveID( int& id )
{
	if( m_UsedIDs.find( id ) == m_UsedIDs.end() )
	{
		m_UsedIDs.insert( id );
		return true;
	}
	return false;
}