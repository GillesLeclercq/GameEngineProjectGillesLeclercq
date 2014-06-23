#pragma once


#include <Windows.h>
#include "GameLoader.h"
#include "GameObjectManager.h"
#include "GameObjectFactory.h"
#include "GameLoader.h"

#include "IGraphics.h"
#include "IAi.h"
#include "IGameOption.h"
#include "IWindow.h"
#include "IMeshManager.h"
#include "ITransfoManager.h"
#include "ICameraManager.h"
#include "ILightManager.h"
#include "Input.h"


class GameLoader;

class Game
{
private:
	GameObjectManager*	m_pGOManager;
	GameObjectFactory*	m_pGOFactory;

	GameLoader*			m_pGameLoader;

	IWindow*			m_pWindow;
	IGraphics*			m_pGraphics;
	IAi*				m_pAI;
	IGameOption*		m_pGameOption;
	IShaderManager*		m_pShaderManager;
	IMeshManager*		m_pMeshManager;
	ITransfoManager*	m_pTransoManager;
	ICameraManager*		m_pCameraManager;
	ILightManager*		m_pLightManager;
	Input*				m_pInput;
	
	bool m_IsRunning;

public:
	Game();
	~Game() { CleanUp(); }

	void Initialize();
	void Launch(HINSTANCE hinstance, int& nCmdShow);
	void HandleMsg( const MSG* msg );
	void Update( float& frameTime );
	void Draw();

	void SetWindow( IWindow* pWindowImpl ) { m_pWindow = pWindowImpl; } 
	void SetGraphics( IGraphics* pGraphImpl ) { m_pGraphics = pGraphImpl; } 
	void SetAI( IAi* pAIImpl ) { m_pAI = pAIImpl; }
	void SetGameOption( IGameOption* pGameOptionImpl ) { m_pGameOption = pGameOptionImpl; }
	void SetShaderManager( IShaderManager* pShaderManager ) { m_pShaderManager = pShaderManager; }
	void SetMeshManager ( IMeshManager* pMeshManager ) { m_pMeshManager = pMeshManager; }
	void SetTransfoManager ( ITransfoManager* pTransoManager) { m_pTransoManager = pTransoManager; }
	void SetCameraManager ( ICameraManager* pCameraManager) { m_pCameraManager = pCameraManager; }
	void SetLightManager ( ILightManager* pLightManager) { m_pLightManager = pLightManager; }
	void SetInput ( Input* pInput) { m_pInput = pInput ; }

	IGameOption* GetGameOption() const { return m_pGameOption; }
	IGraphics* GetGraphics () const { return m_pGraphics; }
	GameObjectManager* GetGOManager() const { return m_pGOManager; }
	ILightManager* GetLightManager() const { return m_pLightManager; }

	void LoadGameObjects(std::string gameObjectsFilename) { m_pGOManager->LoadGameObjects( gameObjectsFilename.c_str() ) ; }

	bool IsRunning() const { return m_IsRunning; }

	void CleanUp();
};