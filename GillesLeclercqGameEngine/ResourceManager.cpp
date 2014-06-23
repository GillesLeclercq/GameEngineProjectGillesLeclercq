#include "ResourceManager.h"

using namespace std;

//----------------------------------------------------------------------
ResourceManager::~ResourceManager()
{
	for( auto loader : m_pResLoadersMap )
	{
		SAFE_DELETE( loader.second );
	}
}

//----------------------------------------------------------------------
bool ResourceManager::RegisterResourceLoader( string fileExt, IResourceLoader* pResLoader )
{
	std::string lowFileExt = StringUtilities::ToLower( fileExt );

	auto findIt = m_pResLoadersMap.find( lowFileExt );
	if( findIt == m_pResLoadersMap.end() )
	{
		m_pResLoadersMap[ lowFileExt ] = pResLoader;
		return true;
	}
	return false;
}

//----------------------------------------------------------------------
IResourcePtr ResourceManager::GetResource( std::string file )
{
	std::string fileLow = StringUtilities::ToLower( file );

	auto findIt = m_pResMap.find( fileLow );
	
	if( findIt == m_pResMap.end() )
	{
		return _LoadFromFile( file );
	}
	
	return findIt->second; 
}

//----------------------------------------------------------------------
IResourcePtr ResourceManager::_LoadFromFile( std::string file )
{
	string ext = StringUtilities::GetExtension( file );
	ext = StringUtilities::ToLower( ext );

	auto findItLoader = m_pResLoadersMap.find( ext );
	if( findItLoader != m_pResLoadersMap.end() )
	{
		string lowFile = StringUtilities::ToLower( file );
		IResourcePtr newRes = findItLoader->second->LoadFromFile( file );
		if( newRes != nullptr )
		{
			m_pResMap[ lowFile ] = newRes;
		}
		return newRes;
	}
	return IResourcePtr();
}