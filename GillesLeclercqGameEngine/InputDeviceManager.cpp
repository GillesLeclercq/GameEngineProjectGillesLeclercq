#include "InputDeviceManager.h"

//----------------------------------------------------------------------
// Initialize the keyboard and the first controller ports. Stop at the first port with no controller.
InputDeviceManager::InputDeviceManager()
{
	m_pKeyboard.reset( new KeyboardDevice() );

	for( int i = 0; i<4; i++ )
	{
		m_pXInputDevices[i].reset( new XInputDevice(i));
		if( !m_pXInputDevices[i]->Initialize() )
		{
			break;
		}
	}
}

//----------------------------------------------------------------------
// Refresh state of connected controllers.
void InputDeviceManager::RefreshControllers()
{
	std::set<int> disconnectedDevices;
	for( auto xinput : m_pXInputDevices )
	{
		if( !xinput.second->Refresh() )
		{
			disconnectedDevices.insert(xinput.first);
		}
	}

	for( auto d : disconnectedDevices )
	{
		m_pXInputDevices.erase(d);
	}
}

//----------------------------------------------------------------------
WkXInputDevicePtr InputDeviceManager::GetController( int port ) const
{ 
	WkXInputDevicePtr result = WkXInputDevicePtr();
	auto findIt = m_pXInputDevices.find(port);
	if( findIt != m_pXInputDevices.end() )
	{
		result = findIt->second;
	}
	return result;
}