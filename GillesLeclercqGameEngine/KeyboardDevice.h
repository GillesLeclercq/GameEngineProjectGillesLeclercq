#pragma once

#include <memory>
#include <map>
#include <string>

#include "ButtonSet.h"

class KeyboardDevice : public ButtonSet
{
private:
	static std::map<std::string, int> s_StrToID;

public:
	KeyboardDevice();
	~KeyboardDevice() {}

	int VStringToInputID( std::string& code );
};

typedef std::shared_ptr<KeyboardDevice> KeyboardPtr;
typedef std::weak_ptr<KeyboardDevice> WkKeyboardPtr;