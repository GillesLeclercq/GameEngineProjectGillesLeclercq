#pragma once

#include "GameObjectManager.h"
#include "Transformation.h"

#include "EventManager.h"
#include "Event_CreateObject.h"
#include "Event_DeleteObject.h"

class ITransfoManager
{
protected:

	std::map<int, Transformation*>	m_pTransformations;

public:

	virtual bool VInitialize(GameObjectManager* goManager) = 0;

	virtual ~ITransfoManager();

	bool RegisterGameObject( GameObject* newGO );

	void OnDestroyGO( IEventPtr evt );
	void OnCreateGO( IEventPtr evt );

};