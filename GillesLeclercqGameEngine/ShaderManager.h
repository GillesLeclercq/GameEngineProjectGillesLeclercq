#pragma once
#include <map>
#include <string>

#include "IShaderManager.h"
#include "Event_CreateShader.h"


class ShaderManager : public IShaderManager
{
private:

public:

	bool VInitialize(GameObjectManager* goManager);

	bool CreateShader(IEventPtr evt);

};