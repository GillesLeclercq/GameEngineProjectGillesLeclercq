#pragma once

#include "GameObjectManager.h"
#include "Shader.h"

#include "EventManager.h"
#include "Event_CreateObject.h"
#include "Event_DeleteObject.h"
#include "Event_CreateGraphics.h"

class IShaderManager
{
protected:

	std::map<int, Shader*>	m_pShaders;

public:

	virtual bool VInitialize(GameObjectManager* goManager) = 0;

	virtual ~IShaderManager();

	bool RegisterGameObject( GameObject* newGO );

	void OnDestroyGO( IEventPtr evt );
	void OnCreateGO( IEventPtr evt );

};