#pragma once

#include "GameObjectManager.h"
#include "DirectionalLightContainer.h"
#include "PointLightContainer.h"

#include "EventManager.h"
#include "Event_CreateObject.h"
#include "Event_DeleteObject.h"

class ILightManager
{
protected:

	std::map<int, DirectionalLightContainer*>	m_pDirectionalLights;
	std::map<int, PointLightContainer*>			m_pPointLights;

public:

	virtual bool VInitialize(GameObjectManager* goManager) = 0;

	virtual ~ILightManager();

	bool RegisterGameObject( GameObject* newGO );

	void OnDestroyGO( IEventPtr evt );
	void OnCreateGO( IEventPtr evt );

	std::vector<DirectionalLight> GetVectorDirectionalLights();
	std::vector<PointLight> GetVectorPointLights();
};