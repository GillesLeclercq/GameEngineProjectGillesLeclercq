#pragma once

#include "IEvent.h"
#include <Windows.h>

class Event_LookForDevices : public IEvent
{
private:

	static const unsigned long s_EvtType = 0x449e7610;

public:
	Event_LookForDevices() {}

	virtual unsigned long VGetEvtType() const override { return s_EvtType; }

	static const unsigned long& EventType() { return s_EvtType; }
};

