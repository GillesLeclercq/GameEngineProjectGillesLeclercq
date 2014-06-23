#pragma once

#include "IAi.h"
#include "LuaStateManager.h"
#include "GameObject.h"

#include "BasicScriptComponent.h"
#include "TestComponent.h"

class LuaAi : public IAi
{
public:
	LuaAi(): IAi() {}
	~LuaAi() {}

	bool VInitialize( GameObjectManager* pGOManager ) override;
};