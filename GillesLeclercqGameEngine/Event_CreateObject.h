#pragma once

#include <memory>

#include "IEvent.h"
#include "GameObject.h"

class Event_CreateObject : public IEvent
{
private:
	static const unsigned long s_EvtType = 0x1b16d8fd;

	GameObject* m_pNewGO;

public:
	Event_CreateObject( GameObject* newGO ): m_pNewGO( newGO ) {}

	GameObject* GetNewGameObject() const { return m_pNewGO; }

	unsigned long VGetEvtType() const override { return s_EvtType; }
	static unsigned long EventType() { return s_EvtType; }
};