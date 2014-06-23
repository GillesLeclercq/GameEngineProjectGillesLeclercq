#pragma once

#include <memory>
#include <string>

class IResource
{
public:
	virtual std::string VGetType() const = 0;
	virtual void Dispose() = 0;
};

typedef std::shared_ptr<IResource> IResourcePtr;