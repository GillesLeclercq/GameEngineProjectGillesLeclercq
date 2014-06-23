#pragma once

#include "IEvent.h"
#include <Windows.h>

class Event_SendHwnd : public IEvent
{
private:
	HWND* m_Hwnd;

	static const unsigned long s_EvtType = 0x7bfe54fe;

public:
	Event_SendHwnd( HWND* Hwnd ): m_Hwnd( Hwnd ) {}

	HWND* GetHwnd() const { return m_Hwnd; }

	virtual unsigned long VGetEvtType() const override { return s_EvtType; }

	static const unsigned long& EventType() { return s_EvtType; }
};

