#pragma once

#include "IEvent.h"
#include <Windows.h>

class Event_CreateWindow : public IEvent
{
private:
	
	HINSTANCE* m_pHInstance;
	int* m_pCmdShow;
	int* m_pWidth;
	int* m_pLength;
	bool m_Fullscreen;

	static const unsigned long s_EvtType = 0x3dcef9ff;
public:
	Event_CreateWindow( HINSTANCE* HInstance , int& CmdShow , int& Width , int& Length, bool& Fullscreen): 
		m_pHInstance( HInstance ) , m_pCmdShow ( &CmdShow ) , m_pWidth (&Width) , m_pLength (&Length) , m_Fullscreen ( Fullscreen ) { } ;

	HINSTANCE* GetHInstance() const { return m_pHInstance; }
	int* GetCmdShow() const { return m_pCmdShow; }
	int* GetWidth() const { return m_pWidth; }
	int* GetLength() const { return m_pLength; }
	bool GetFullscreen() const { return m_Fullscreen; }

	virtual unsigned long VGetEvtType() const override { return s_EvtType; }

	static const unsigned long& EventType() { return s_EvtType; }
};