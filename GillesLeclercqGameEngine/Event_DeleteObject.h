#pragma once

#include "IEvent.h"

class Event_DeleteObject : public IEvent
{
private:
	int m_DeletedID;

public:
	Event_DeleteObject( int& id ): m_DeletedID( id ) {}
	~Event_DeleteObject() {}
	int GetDeletedID() const { return m_DeletedID; }


private:
	static const unsigned long s_EvtType = 0x437f71d5;
public:
	virtual unsigned long VGetEvtType() const override { return s_EvtType; }
	static const unsigned long& EventType() { return s_EvtType; }
};
