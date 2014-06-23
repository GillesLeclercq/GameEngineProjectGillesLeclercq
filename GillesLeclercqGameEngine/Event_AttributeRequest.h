#pragma once

#include <string>

#include "IEvent.h"

class Event_AttributeRequest : public IEvent
{
private:
	int m_SenderID;
	int m_ReceiverID;
	std::string m_AttID;

public:
	Event_AttributeRequest( int& sender, int& receiver, std::string& attId ): m_SenderID( sender ), m_ReceiverID( receiver ), m_AttID( attId ) {}
	~Event_AttributeRequest() {}

	int GetSender() const { return m_SenderID; }
	int GetReceiver() const { return m_ReceiverID; }
	std::string GetAttributeID() const { return m_AttID; }
	
private:
	static const unsigned long s_EvtType = 0xfc645d10;

public:
	virtual unsigned long VGetEvtType() const override { return s_EvtType; }
	static const unsigned long& EventType() { return s_EvtType; }
};
