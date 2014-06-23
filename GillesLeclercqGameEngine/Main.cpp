#include "Game.h"
#include "Timer.h"
#include "Graphics.h"
#include "LuaAi.h"



int WINAPI wWinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow )
{
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	Game* game = new Game();
	Timer gameTimer( 60 ); // Limit at 60 FPS
	game->Initialize();
	game->Launch(hInstance, nCmdShow);
	MSG msg = {0};
	gameTimer.InitializeStartTime();
	while( msg.message != WM_QUIT )
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
			game->HandleMsg(&msg);
            DispatchMessage(&msg);
        }
        else
        {
			float frameTime = gameTimer.GetLastFrameTime();
			game->Update( frameTime );
			game->Draw();
        }
	}
	SAFE_DELETE(game);
}