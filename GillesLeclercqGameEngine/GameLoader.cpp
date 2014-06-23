#include "GameLoader.h"
#include "Game.h"

using namespace std;

//----------------------------------------------------------------------
int GameLoader::Loading(std::string filename, Game* game)
{
	XmlMediator* xmlMediator = TinyXmlLoader::Instance().LoadFile(filename.c_str());
	if (!xmlMediator)
		return 1;

	auto resultShader = xmlMediator->GetChildren((string)"Shader");
	if (resultShader.size() != 1)
	{
		cerr << "ERROR: Fail to load Shader (wrong filename).";
	}
	LoadShaderManager(resultShader.front()->GetContent(), game);

	auto resultAi = xmlMediator->GetChildren((string)"Ai");
	if (resultAi.size() != 1)
	{
		cerr << "ERROR: Fail to load AI (wrong filename).";
		return 1 ;
	}
	LoadAi(resultAi.front()->GetContent(), game);

	auto resultGameOption = xmlMediator->GetChildren((string)"GameOption");
	if (resultGameOption.size() != 1)
	{
		cerr << "ERROR: Fail to load GameOption (wrong filename).";
		return 1 ;
	}
	LoadGameOption(resultGameOption.front()->GetContent(), game);

	auto resultWindow = xmlMediator->GetChildren((string)"Window");
	if (resultWindow.size() != 1)
	{
		cerr << "ERROR: Fail to load Window (wrong filename).";
		return 1;
	}
	LoadWindows(resultWindow.front()->GetContent(), game);

	
	auto resultLightManager = xmlMediator->GetChildren((string)"Light");
	if (resultLightManager.size() != 1)
	{
		cerr << "ERROR: Fail to load Light (wrong filename).";
		return 1;
	}
	LoadLightManager(resultLightManager.front()->GetContent(), game);

	auto resultGraphics = xmlMediator->GetChildren((string)"Graphics");
	if (resultGraphics.size() != 1)
	{
		cerr << "ERROR: Fail to load Graphics (wrong filename).";
		return 1;
	}
	LoadGraphics(resultGraphics.front()->GetContent(), game);

	auto resultMesh = xmlMediator->GetChildren((string)"Mesh");
	if (resultMesh.size() != 1)
	{
		cerr << "ERROR: Fail to load Meshes (wrong filename).";
		return 1;
	}
	LoadMeshManager(resultMesh.front()->GetContent(), game);

	auto resultTransfo = xmlMediator->GetChildren((string)"Transformation");
	if (resultTransfo.size() != 1)
	{
		cerr << "ERROR: Fail to load Transformation (wrong filename).";
		return 1;
	}
	LoadTransfoManager(resultTransfo.front()->GetContent(), game);

	auto resultCameraManager = xmlMediator->GetChildren((string)"Camera");
	if (resultCameraManager.size() != 1)
	{
		cerr << "ERROR: Fail to load Camera (wrong filename).";
		return 1;
	}
	LoadCameraManager(resultCameraManager.front()->GetContent(), game);

	auto resultInput = xmlMediator->GetChildren((string)"Input");
	if (resultInput.size() != 1)
	{
		cerr << "ERROR: Fail to load Input (wrong filename).";
		return 1;
	}
	LoadInput(resultInput.front()->GetContent(), game);

	auto resultGameObject = xmlMediator->GetChildren((string)"GameObjects");
	if (resultGameObject.size() != 1)
	{
		cerr << "ERROR: Fail to load GameObjects (wrong filename).";
		return 1;
	}
	LoadGameObjects(resultGameObject.front()->GetContent(), game);


	return 0;
}

//---------------------------------------------------------------------
int GameLoader::LoadGameOption(string gameOptionFilename, Game* game)
{
	if (gameOptionFilename == "GameOption.xml")
	{
		GameOption* gameOption = new GameOption();
		if (!gameOption->LoadOptions(gameOptionFilename))
		{
			delete gameOption;
			return 1;
		}
		game->SetGameOption(gameOption);
	}
	return 0;
}

//---------------------------------------------------------------------
int GameLoader::LoadGraphics(string graphicsFilename, Game* game)
{
	if (graphicsFilename == "Graphics.xml")
	{
		Graphics* graphics = new Graphics();
		game->SetGraphics(graphics);
		graphics->SetLightManager(game->GetLightManager());
		graphics->VInitialize(game->GetGOManager());
	}
	return 0;
}

//---------------------------------------------------------------------
int GameLoader::LoadWindows(string windowsFilename, Game* game)
{
	if (windowsFilename == "Window.xml")
	{
		Window* window = new Window();
		if (!window->Init())
		{
			delete window;
			return 1;
		}
		game->SetWindow(window);
	}
	return 0;
}

//---------------------------------------------------------------------
int GameLoader::LoadAi(string aiFilename, Game* game)
{
	if (aiFilename == "LuaAi.xml")
	{
		LuaAi* Ai = new LuaAi();
		game->SetAI(Ai);
		Ai->VInitialize(game->GetGOManager());
	}
	return 0;
}

//---------------------------------------------------------------------
int GameLoader::LoadGameObjects(string gameObjectsFilename, Game* game)
{
	if (gameObjectsFilename == "GameObjects.xml")
	{
		game->LoadGameObjects(gameObjectsFilename);
	}
	return 0;
}

int GameLoader::LoadShaderManager(std::string shaderManagerFilename, Game* game)
{
	if (shaderManagerFilename == "Shader.xml")
	{
		ShaderManager* shaderManager = new ShaderManager();
		shaderManager->VInitialize(game->GetGOManager());
		game->SetShaderManager(shaderManager);
	}
	return 0;
}

int GameLoader::LoadMeshManager(std::string meshManagerFileName, Game* game)
{
	if (meshManagerFileName == "Mesh.xml")
	{
		MeshManager* meshManager = new MeshManager();
		meshManager->VInitialize(game->GetGOManager());
		game->SetMeshManager(meshManager);
	}
	return 0;
}

int GameLoader::LoadTransfoManager(std::string transfoManagerFileName, Game* game)
{
	if (transfoManagerFileName == "Transformation.xml")
	{
		TransfoManager* transfoManager = new TransfoManager();
		transfoManager->VInitialize(game->GetGOManager());
		game->SetTransfoManager(transfoManager);
	}
	return 0;
}

int GameLoader::LoadCameraManager(std::string cameraManagerFileName, Game* game)
{
	if (cameraManagerFileName == "CameraManager.xml")
	{
		CameraManager* cameraManager = new CameraManager();
		cameraManager->VInitialize(game->GetGOManager());
		game->SetCameraManager(cameraManager);
	}
	return 0;
}

int GameLoader::LoadLightManager(std::string cameraManagerFileName, Game* game)
{
	if (cameraManagerFileName == "LightManager.xml")
	{
		LightManager* lightManager = new LightManager();
		lightManager->VInitialize(game->GetGOManager());
		game->SetLightManager(lightManager);
	}
	return 0;
}

int GameLoader::LoadInput (std::string inputFileName, Game* game)
{
	if (inputFileName == "InputProfiles.txt")
	{
		Input* input = new Input();

		std::ifstream fin( inputFileName );
		if( fin.is_open() )
		{
			input->Initialize( game->GetGOManager() );
			input->InitializeProfiles( fin );
		}
		game->SetInput(input);
	}
	return 0;
}