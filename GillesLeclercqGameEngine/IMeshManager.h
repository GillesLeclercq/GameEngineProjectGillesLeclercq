#pragma once

#include "GameObjectManager.h"
#include "Mesh.h"

#include "EventManager.h"
#include "Event_CreateObject.h"
#include "Event_DeleteObject.h"

class IMeshManager
{
protected:

	std::map<int, Mesh*>	m_pMesh;

public:

	virtual bool VInitialize(GameObjectManager* goManager) = 0;

	virtual ~IMeshManager();

	bool RegisterGameObject( GameObject* newGO );

	void OnDestroyGO( IEventPtr evt );
	void OnCreateGO( IEventPtr evt );

};