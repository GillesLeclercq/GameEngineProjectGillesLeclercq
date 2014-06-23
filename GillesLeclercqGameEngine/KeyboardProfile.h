#pragma once

#include <set>
#include <string>
#include <iostream>
#include <fstream>

#include "ButtonProfile.h"
#include "InputDeviceManager.h"
#include "KeyboardDevice.h"
#include "Utilities.h"

class KeyboardProfile : public ButtonProfile
{
private:
	WkKeyboardPtr m_pKeyboard;

protected:
	KeyboardProfile( WkDeviceManagerPtr pDeviceMgr, int port = -1 );
	bool VInitialize( std::ifstream& fin, WkActionTranslatorPtr pActionTransl ) override;
public:
	~KeyboardProfile() {}

	void VProcessInput() override;

	static IInputProfile* CreateProfile( std::ifstream& fin, WkDeviceManagerPtr pInputDeviceMgr, WkActionTranslatorPtr pActionTransl, int& port );
};