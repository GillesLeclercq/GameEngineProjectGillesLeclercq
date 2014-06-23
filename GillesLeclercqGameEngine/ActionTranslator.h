#pragma once

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>

#include "Utilities.h"

enum ACTION
{
	ACTION_NONE = -1,
	ACTION_UP = 0, 
	ACTION_DOWN = 1, 
	ACTION_LEFT = 2, 
	ACTION_RIGHT = 3, 

	ACTION_LEFTTRIGGER = 4,
	ACTION_RIGHTTRIGGER = 5,

	ACTION_LEFTSTICK = 6,
	ACTION_RIGHTSTICK = 7
};

class ActionTranslator
{
private:
	std::map<std::string, ACTION> m_StrToActionMap;

public:
	ActionTranslator( std::ifstream& actionFile );
	~ActionTranslator() {}

	int GetAction( std::string word );
};

typedef std::shared_ptr<ActionTranslator> ActionTranslatorPtr;
typedef std::weak_ptr<ActionTranslator> WkActionTranslatorPtr;