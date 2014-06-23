#pragma once
#include "XmlMediator.h"
#include "TinyXmlLoader.h"
#include "EventManager.h"

#include <set>

#include "LuaAi.h"
#include "GameOption.h"
#include "Graphics.h"
#include "Window.h"
#include "ShaderManager.h"
#include "MeshManager.h"
#include "TransfoManager.h"
#include "CameraManager.h"
#include "LightManager.h"


class Game;

class GameLoader
{

public:
	GameLoader(void) {};
	~GameLoader(void) {};

	int Loading(std::string filename, Game* game);

	int LoadGameOption(std::string gameOptionFilename, Game* game);
	int LoadGraphics(std::string graphicsFilename, Game* game);
	int LoadWindows(std::string windowsFilename, Game* game);
	int LoadAi(std::string aiFilename, Game* game);
	int LoadGameObjects(std::string gameObjectsFilename, Game* game);
	int LoadShaderManager(std::string shaderManagerFilename, Game* game);
	int LoadMeshManager(std::string meshManagerFileName, Game* game);
	int LoadTransfoManager(std::string transfoManagerFileName, Game* game);
	int LoadCameraManager(std::string cameraManagerFileName, Game* game);
	int LoadLightManager(std::string cameraManagerFileName, Game* game);
	int LoadInput (std::string inputFileName, Game* game);

};

