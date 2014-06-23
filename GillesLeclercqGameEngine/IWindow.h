#pragma once

#include "EventManager.h"

class IWindow
{
public:
	
	virtual ~IWindow() {};

	virtual bool Init() = 0;
};