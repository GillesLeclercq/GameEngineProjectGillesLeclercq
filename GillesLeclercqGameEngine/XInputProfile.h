#pragma once

#include "XInputDevice.h"
#include "ButtonProfile.h"
#include "AnalogicProfile.h"
#include "StickProfile.h"
#include "InputDeviceManager.h"

class XInputProfile : public ButtonProfile, public AnalogicProfile, public StickProfile
{
private: 
	WkXInputDevicePtr m_pDevice;

protected:
	XInputProfile( WkDeviceManagerPtr pDevice, int port );
	bool VInitialize( std::ifstream& fin, WkActionTranslatorPtr pActionTransl ) override;

public:
	~XInputProfile() {}

	void VProcessInput() override;

	static IInputProfile* CreateProfile( std::ifstream& fin, WkDeviceManagerPtr pInputDeviceMgr, WkActionTranslatorPtr pActionTransl, int& port );
};