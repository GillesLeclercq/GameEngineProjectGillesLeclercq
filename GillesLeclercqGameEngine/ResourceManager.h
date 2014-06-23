#pragma once

#include <map>
#include <list>

#include "IResource.h"
#include "IResourceLoader.h"
#include "Utilities.h"

class ResourceManager
{
private:
	std::map<std::string, IResourcePtr>		m_pResMap;
	std::map<std::string, IResourceLoader*>	m_pResLoadersMap;

	IResourcePtr _LoadFromFile( std::string file );

public:
	ResourceManager()	{}
	~ResourceManager();

	bool RegisterResourceLoader( std::string fileExt, IResourceLoader* pResLoader );
	
	IResourcePtr GetResource( std::string file );
};