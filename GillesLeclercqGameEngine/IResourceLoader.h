#pragma once

#include <string>

#include "IResource.h"

class IResourceLoader
{
public:
	virtual IResourcePtr LoadFromFile( std::string file ) const = 0;
};