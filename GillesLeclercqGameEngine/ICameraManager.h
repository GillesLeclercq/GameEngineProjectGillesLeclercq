#pragma once

#include "GameObjectManager.h"
#include "Camera.h"

#include "EventManager.h"
#include "Event_CreateObject.h"
#include "Event_DeleteObject.h"

class ICameraManager
{
protected:

	std::map<int, Camera*>	m_pCameras;
	Camera*					m_pCurrentCamera;

public:

	virtual bool VInitialize(GameObjectManager* goManager) = 0;

	virtual ~ICameraManager();

	bool RegisterGameObject( GameObject* newGO );

	void OnDestroyGO( IEventPtr evt );
	void OnCreateGO( IEventPtr evt );

};