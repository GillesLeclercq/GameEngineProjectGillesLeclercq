/*#include "Game.h"

using namespace std;

//----------------------------------------------------------------------
Game::Game()
{
	m_pGOFactory = nullptr;
	m_pGOManager = nullptr;

	m_pGraphics = nullptr;

	m_IsRunning = false;
}

//----------------------------------------------------------------------
Game::~Game()
{
	SAFE_DELETE( m_pGOManager );
	SAFE_DELETE( m_pGOFactory );

	SAFE_DELETE( m_pGraphics );
}

//----------------------------------------------------------------------
void Game::Initialize() 
{ 
	m_pGOFactory = new GameObjectFactory();
	m_pGOManager = new GameObjectManager( m_pGOFactory );

	if( m_pGraphics != nullptr )
	{
		cout << "Initializing Graphics" << endl;
		m_pGraphics->VInitialize( m_pGOManager );
	}
	else 
	{
		// TODO: NullObject => IGraphics implementation with functions that do nothing.
	}

	if( m_pAI != nullptr )
	{
		cout << "Initializing AI" << endl;
		m_pAI->VInitialize( m_pGOManager );
	}

	if( m_pInput != nullptr )
	{
		cout << "Initializing Input" << endl;
		m_pInput->Initialize( m_pGOManager );
		std::ifstream fin( "InputProfiles.txt" );
		if( fin.is_open() )
		{
			m_pInput->InitializeProfiles( fin );
		}
		fin.close();

	}

	cout << "Loading GO" << endl;
	m_pGOManager->LoadGameObjects( "GameObjects.xml" );

	m_IsRunning = true; 
}

//----------------------------------------------------------------------
void Game::Update( float& frameTime ) 
{ 
	cout << "Updating" << endl;
	m_pGOManager->Update( frameTime );

	cout << "Processing inputs" << endl;
	m_pInput->ProcessInputs();
}

//----------------------------------------------------------------------
void Game::Draw() 
{ 
	m_pGraphics->VDraw(); 
}
*/

#include "Game.h"

//----------------------------------------------------------------------
Game::Game()
{
	m_pGOFactory = nullptr;
	m_pGOManager = nullptr;

	m_pGameLoader = nullptr;
	m_pWindow = nullptr;
	m_pGraphics = nullptr;
	m_pAI = nullptr;
	m_pGameOption = nullptr;
	m_pShaderManager = nullptr;
	m_pMeshManager = nullptr;
	m_pTransoManager = nullptr;

	m_IsRunning = false;
}

//----------------------------------------------------------------------
void Game::Initialize() 
{ 
	m_pGOFactory = new GameObjectFactory();
	m_pGOManager = new GameObjectManager( m_pGOFactory );

	m_pGameLoader = new GameLoader();

	m_pGameLoader->Loading("GameLoader.xml", this);

}

//----------------------------------------------------------------------
void Game::Launch(HINSTANCE hinstance, int& nCmdShow)
{
	
	int width = GetGameOption()->GetWidth();
	int length = GetGameOption()->GetLength();
	bool fullscreen = GetGameOption()->GetFullScreen();

	EventManager::Instance().SendEvent ( 
		std::make_shared<Event_CreateWindow>(
			Event_CreateWindow(&hinstance , nCmdShow, width , length , fullscreen)));

	EventManager::Instance().SendEvent ( 
		std::make_shared<Event_LookForHwnd>(
			Event_LookForHwnd()));

	EventManager::Instance().SendEvent ( 
		std::make_shared<Event_LookForDevices>(
			Event_LookForDevices()));

		m_IsRunning = true; 
}

//----------------------------------------------------------------------
void Game::HandleMsg( const MSG* msg )
{
	switch( msg->message )
	{
	case WM_KEYDOWN:
		m_pInput->OnKeyDown(msg->wParam);
		break;
	case WM_KEYUP:
		m_pInput->OnKeyUp(msg->wParam);
		break;
	}
}

//----------------------------------------------------------------------
void Game::Update( float& frameTime ) 
{ 
	m_pInput->ProcessInputs();

	m_pGOManager->Update( frameTime );
}

//----------------------------------------------------------------------
void Game::Draw() 
{ 
	m_pGraphics->VDraw(); 
}

void Game::CleanUp()
{
	SAFE_DELETE( m_pGOManager );
	SAFE_DELETE( m_pGOFactory );

	SAFE_DELETE( m_pGameLoader);

	SAFE_DELETE( m_pWindow );
	SAFE_DELETE( m_pGraphics );
	SAFE_DELETE( m_pAI );
	SAFE_DELETE( m_pGameOption );
	SAFE_DELETE( m_pShaderManager );
	SAFE_DELETE( m_pMeshManager );
	SAFE_DELETE( m_pTransoManager );
	SAFE_DELETE( m_pLightManager );
	SAFE_DELETE( m_pInput );
}