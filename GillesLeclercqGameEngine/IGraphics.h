#pragma once 

#include <memory>
#include <iostream>
#include <map>

#include "GameObjectManager.h"
#include "IShaderManager.h"

#include "GraphicsComponent.h"
#include "EventManager.h"
#include "Event_CreateObject.h"
#include "Event_DeleteObject.h"
#include "Event_CreateGraphics.h"

class IGraphics
{
protected:
	std::map<int, GraphicsComponent*>	m_pGraphicComponents;

public:
	virtual bool VInitialize( GameObjectManager* goManager ) = 0;
	virtual ~IGraphics() {};
	
	bool RegisterGameObject( GameObject* newGO );

	virtual void VDraw() = 0;

	// Delegates
	void OnDestroyGO( IEventPtr evt );
	void OnCreateGO( IEventPtr evt );

};