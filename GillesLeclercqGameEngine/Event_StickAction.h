#pragma once

#include <utility>

#include "IEvent.h"

class Event_StickAction : public IEvent
{
private:
	int m_Target;
	int m_Action;
	std::pair<float, float> m_Position;

public:
	Event_StickAction( int& target, int& action, std::pair<float, float> position ): 
		m_Target( target ), m_Action( action ), m_Position( position ) {}

	int GetTarget() const { return m_Target; }
	int GetAction() const { return m_Action; }
	std::pair<float, float> GetPosition() const { return m_Position; }

private:
	static const unsigned long s_EvtType = 0x67a4e328;
public:
	unsigned long VGetEvtType() const override { return s_EvtType; }
	static unsigned long EventType() { return s_EvtType; }
};