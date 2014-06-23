#pragma once

#include "IGameOption.h"
#include <string>
#include "XmlMediator.h"
#include "TinyXmlLoader.h"

class GameOption : public IGameOption
{

public:

	bool LoadOptions(std::string fileName);

};