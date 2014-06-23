#pragma once

#include <memory>
#include <map>
#include <set>

#include "KeyboardDevice.h"
#include "XInputDevice.h"

class InputDeviceManager
{
private:
	KeyboardPtr m_pKeyboard;

	std::map<int, XInputDevicePtr> m_pXInputDevices;

public:
	InputDeviceManager();
	~InputDeviceManager() {}

	void RefreshControllers();

	WkKeyboardPtr GetKeyboard() const { return WkKeyboardPtr( m_pKeyboard ); }
	WkXInputDevicePtr GetController( int port ) const;
};

typedef std::shared_ptr<InputDeviceManager> DeviceManagerPtr;
typedef std::weak_ptr<InputDeviceManager> WkDeviceManagerPtr;