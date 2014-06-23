#pragma once

#include <iostream>
#include <map>
#include <d3d11_1.h>
#include <directxmath.h>

#include "ITransfoManager.h"
#include "IComponent.h"

#include "Event_LookForDevices.h"
#include "Event_CreateShader.h"


class TransfoManager : public ITransfoManager
{
public:
	TransfoManager() {}
	~TransfoManager() {}

	bool VInitialize( GameObjectManager* goManager ) override;

};