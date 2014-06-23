#pragma once

#include "IEvent.h"
#include <Windows.h>

class Event_CreateGraphics : public IEvent
{
private:
	
	HWND* m_pHwnd;

	static const unsigned long s_EvtType = 0xef9a705;
public:
	Event_CreateGraphics( HWND* Hwnd): 
		m_pHwnd( Hwnd ) { } ;

	HWND* GetHwnd() const { return m_pHwnd; }

	virtual unsigned long VGetEvtType() const override { return s_EvtType; }

	static const unsigned long& EventType() { return s_EvtType; }

};
