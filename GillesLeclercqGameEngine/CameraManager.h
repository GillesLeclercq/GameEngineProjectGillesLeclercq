#pragma once

#include <iostream>
#include <map>
#include <d3d11_1.h>
#include <directxmath.h>

#include "ICameraManager.h"
#include "IComponent.h"

#include "Event_LookForDevices.h"
#include "Event_CreateShader.h"


class CameraManager : public ICameraManager
{
public:
	CameraManager() {}
	~CameraManager() {}

	bool VInitialize( GameObjectManager* goManager ) override;

	void SetNewCurrentCamera(IEventPtr evt);

};