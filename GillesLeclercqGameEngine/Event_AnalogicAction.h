#pragma once

#include "IEvent.h"

class Event_AnalogicAction : public IEvent
{
private:
	int m_Target;
	int m_Action;
	float m_Factor;

public:
	Event_AnalogicAction( int& target, int& action, float factor = 1.0f ): 
		m_Target( target ), m_Action( action ), m_Factor( 1.0f * factor ) {}

	int GetTarget() const { return m_Target; }
	int GetAction() const { return m_Action; }
	float GetFactor() const { return m_Factor; }

private:
	static const unsigned long s_EvtType = 0x3cadad39;
public:
	unsigned long VGetEvtType() const override { return s_EvtType; }
	static unsigned long EventType() { return s_EvtType; }
};