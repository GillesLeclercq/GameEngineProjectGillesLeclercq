#pragma once 

class IEvent
{
public:
	virtual unsigned long VGetEvtType() const = 0;
};

typedef std::shared_ptr<IEvent> IEventPtr;