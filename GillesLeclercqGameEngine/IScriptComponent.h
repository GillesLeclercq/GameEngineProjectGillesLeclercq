#pragma once

#include "IComponent.h"

class IScriptComponent : public IComponent
{
public:
	IScriptComponent( GameObject* pOwner ): IComponent( pOwner ) {}
	virtual ~IScriptComponent() {}

	virtual bool VInitialize( XmlMediator* pComponent ) = 0;
};