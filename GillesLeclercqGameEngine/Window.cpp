#include "Window.h"

using namespace std;

LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
    HDC hdc;

    switch( message )
    {
        case WM_PAINT:
            hdc = BeginPaint( hWnd, &ps );
            EndPaint( hWnd, &ps );
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
}

bool Window::Init()
{
	EventManager::Instance().Bind( Event_CreateWindow::EventType() , (EventDelegate&)fastdelegate::MakeDelegate( this, &Window::CreateWin ) ); 

	EventManager::Instance().Bind( Event_LookForHwnd::EventType() , (EventDelegate&)fastdelegate::MakeDelegate( this, &Window::SendBackHwnd ) ); 

	return true;
}

bool Window::CreateWin(IEventPtr evt)
{
	shared_ptr<Event_CreateWindow> createWindowEvt = static_pointer_cast<Event_CreateWindow>(evt);
	m_HInstance = *createWindowEvt->GetHInstance();
	m_Length = *createWindowEvt->GetLength();
	m_Width = *createWindowEvt->GetWidth();
	m_CmdShow = *createWindowEvt->GetCmdShow();
	m_Fullscreen = createWindowEvt->GetFullscreen();


	WNDCLASSEX wcex;
    wcex.cbSize = sizeof( WNDCLASSEX );
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_HInstance;
    wcex.hIcon = LoadIcon( m_HInstance, ( LPCTSTR ) 109 );
    wcex.hCursor = LoadCursor( nullptr, IDC_ARROW );
    wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"TutorialWindowClass";
    wcex.hIconSm = LoadIcon( wcex.hInstance, ( LPCTSTR ) 109 );
    if( !RegisterClassEx( &wcex ) )
        return false;

    RECT rc = { 0, 0, m_Length, m_Width };
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
	if (!m_Fullscreen){
    m_HandleWin = CreateWindow( L"TutorialWindowClass", L"Project", WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, m_HInstance,
                           nullptr );
	}
	else {
		 m_HandleWin = CreateWindowEx(NULL , L"TutorialWindowClass", L"Project", WS_EX_TOPMOST | WS_POPUP , 0 , 0 , rc.right - rc.left , rc.bottom - rc.top , 
						nullptr , nullptr , m_HInstance , nullptr);
	}
    if( !m_HandleWin )
        return false;

    ShowWindow( m_HandleWin, m_CmdShow );

    return S_OK;
}


void Window::SendBackHwnd(IEventPtr evt)
{
	EventManager::Instance().SendEvent ( 
		std::make_shared<Event_CreateGraphics>(
			Event_CreateGraphics(&m_HandleWin)));
}