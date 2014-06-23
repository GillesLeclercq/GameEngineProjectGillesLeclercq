#pragma once

#include "FastDelegate/FastDelegate.h"

#include "XmlMediator.h"

class GameObject;

class IComponent
{
protected:
	GameObject* m_pOwner;

public:
	IComponent( GameObject* pOwner ) : m_pOwner( pOwner ) {}
	virtual ~IComponent() {}

	virtual bool VInitialize( XmlMediator* pComponent ) = 0;

	virtual const unsigned long& VGetComponentType() const = 0;
};

