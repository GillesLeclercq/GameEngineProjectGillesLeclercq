#pragma once

#include "IWindow.h"
#include <Windows.h>

#include "Event_CreateWindow.h"
#include "Event_LookForHwnd.h"
#include "Event_CreateGraphics.h"

LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

class Window : public IWindow
{									
private:

	HWND		m_HandleWin;
	HINSTANCE	m_HInstance;
	int			m_Length;
	int			m_Width;
	int			m_CmdShow;
	bool		m_Fullscreen;

public:

	Window() {};
	~Window() {};

	bool Init() override ;
	bool CreateWin(IEventPtr evt);

	void SendBackHwnd(IEventPtr evt);

	const HINSTANCE* GetHInstance() const { return &m_HInstance ; }
	const int GetCmdShow() const { return m_CmdShow ; }

};