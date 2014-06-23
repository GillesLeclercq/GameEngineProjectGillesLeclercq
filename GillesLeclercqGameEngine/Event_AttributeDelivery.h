#pragma once

#include <string>

#include "IEvent.h"

class Event_AttributeDelivery : public IEvent
{
private:
	int m_ReceiverID;
	void* m_pValue;

public:
	Event_AttributeDelivery( int id, void* value ): m_ReceiverID( id ), m_pValue( value ) {}
	~Event_AttributeDelivery() {}

	int GetRequester() const { return m_ReceiverID; }
	void* GetValue() const { return m_pValue; }

private:
	static const unsigned long s_EvtType = 0xbd61065a;
public:
	virtual unsigned long VGetEvtType() const override { return s_EvtType; }
	static const unsigned long& EventType() { return s_EvtType; }
};
