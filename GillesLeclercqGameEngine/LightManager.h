#pragma once

#include <iostream>
#include <map>
#include <d3d11_1.h>
#include <directxmath.h>

#include "ILightManager.h"
#include "IComponent.h"



class LightManager : public ILightManager
{
public:
	LightManager() {}
	~LightManager() {}

	bool VInitialize( GameObjectManager* goManager ) override;

};