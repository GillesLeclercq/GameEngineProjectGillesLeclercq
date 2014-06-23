#pragma once

#include "IEvent.h"

class Event_Action : public IEvent
{
private:	
	int m_Target;
	int m_Action;

public:
	Event_Action( int& target, int& action ): m_Target( target ), m_Action( action ) {}

	int GetAction() const { return m_Action; }
	int GetTarget() const { return m_Target; }


private:
	static const unsigned long s_EvtType = 0xf931622;
public:
	unsigned long VGetEvtType() const override { return s_EvtType; }
	static unsigned long EventType() { return s_EvtType; }
};