#pragma once

#include <memory>
#include <map>
#include <set>

#include "FastDelegate/FastDelegate.h"

#include "IEvent.h"

typedef fastdelegate::FastDelegate1<IEventPtr> EventDelegate;

class EventManager
{
private:
	std::map<unsigned long, std::set<EventDelegate>> m_DelegateMap;

	EventManager( const EventManager& )				{}
	EventManager& operator=( const EventManager& )	{}

	EventManager()									{}
	~EventManager()									{}

	static EventManager s_Instance;

public:
	static EventManager& Instance() { return s_Instance; }

	void SendEvent( IEventPtr evt ) const;

	void Bind( const unsigned long& evtType, EventDelegate& evtReceiver );
	bool UnBind( const unsigned long& evtType, EventDelegate& evtReceiver );
};