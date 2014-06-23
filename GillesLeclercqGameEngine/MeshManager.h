#pragma once

#include <iostream>
#include <map>
#include <d3d11_1.h>
#include <directxmath.h>

#include "IMeshManager.h"
#include "IComponent.h"

#include "Event_LookForDevices.h"
#include "Event_CreateShader.h"


class MeshManager : public IMeshManager
{
public:
	MeshManager() {}
	~MeshManager() {}

	bool VInitialize( GameObjectManager* goManager ) override;

};