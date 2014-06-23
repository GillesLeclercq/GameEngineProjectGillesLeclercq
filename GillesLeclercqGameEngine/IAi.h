#pragma once

#include "GameObjectManager.h"

class IAi
{
protected:
	bool m_Initialized;

public:
	IAi(): m_Initialized( false ) {}
	~IAi() {}

	virtual bool VInitialize( GameObjectManager* pGOManager ) = 0;
};