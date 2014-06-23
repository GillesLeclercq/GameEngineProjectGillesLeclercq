#pragma once

#include "IEvent.h"
#include <Windows.h>

class Event_LookForHwnd : public IEvent
{
private:

	static const unsigned long s_EvtType = 0x66ddcbbc;

public:
	Event_LookForHwnd() {}

	virtual unsigned long VGetEvtType() const override { return s_EvtType; }

	static const unsigned long& EventType() { return s_EvtType; }
};
