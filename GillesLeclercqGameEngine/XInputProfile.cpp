#include "XInputProfile.h"

using namespace std;

//----------------------------------------------------------------------
XInputProfile::XInputProfile( WkDeviceManagerPtr pDeviceMgr, int port )
{
	if( auto pDeviceManager = pDeviceMgr.lock() )
	{
		// Setting the device
		m_pDevice = pDeviceManager->GetController( port );
	}
}

//----------------------------------------------------------------------
bool XInputProfile::VInitialize( std::ifstream& fin, WkActionTranslatorPtr pActionTransl )
{
	auto pActiontranslator = pActionTransl.lock();
	auto pDevice = m_pDevice.lock();
	if( fin.is_open() && pActiontranslator)
	{
		if( pDevice )
		{
			string temp;

			if( !InitializeGOID(fin) )
			{
				return false;
			}

			// Mapping button/action
			fin >> temp;
			while( temp != ";" )
			{
				if( StringUtilities::ToLower(temp) == "b" )
				{
					temp = MapButtonToAction( pDevice, pActiontranslator, fin );
				}
				else if( StringUtilities::ToLower(temp) == "a" )
				{
					temp = MapAnalogicToAction( pDevice, pActiontranslator, fin );
				}
				else if( StringUtilities::ToLower(temp) == "s" )
				{
					temp = MapStickToAction( pDevice, pActiontranslator, fin );
				}
				else
				{
					// File format not recognized
					SkipProfileInfo( fin );
					return false;
				}
			}
			return true;
		}
		else
		{
			// No device connected.
			SkipProfileInfo( fin );
			return false;
		}
	}
	return false;
}

//----------------------------------------------------------------------
void XInputProfile::VProcessInput()
{
	ProcessButtonInputs( WkButtonSetPtr(m_pDevice) );
	ProcessAnalogicInputs( WkAnalogicSetPtr(m_pDevice) );
	ProcessStickInputs( WkStickSetPtr(m_pDevice) );
}

//----------------------------------------------------------------------
IInputProfile* XInputProfile::CreateProfile( std::ifstream& fin, WkDeviceManagerPtr pInputDeviceMgr, WkActionTranslatorPtr pActionTransl, int& port )
{
	XInputProfile* NewProfile = new XInputProfile( pInputDeviceMgr, port ); 
	if( NewProfile->VInitialize( fin, pActionTransl ) )
	{
		return NewProfile;
	}
	SAFE_DELETE( NewProfile );
	return nullptr;
}