#include "KeyboardProfile.h"

using namespace std;

//----------------------------------------------------------------------
KeyboardProfile::KeyboardProfile( WkDeviceManagerPtr pDeviceMgr, int port )
{
	if( auto pDeviceManager = pDeviceMgr.lock() )
	{
		// Setting the device
		m_pKeyboard = pDeviceManager->GetKeyboard();
	}
}

//----------------------------------------------------------------------
bool KeyboardProfile::VInitialize( std::ifstream& fin, WkActionTranslatorPtr pActionTransl )
{
	auto pActiontranslator = pActionTransl.lock();
	auto pDevice = m_pKeyboard.lock();
	if( fin.is_open() && pActiontranslator && pDevice )
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
			else // Skip
			{
				do 
				{
					fin >> temp;
				} 
				while( temp != "b" && temp != ";" );
				return false;
			}
		}
		return true;
	}
	return false;
}

//----------------------------------------------------------------------
void KeyboardProfile::VProcessInput()
{
	ProcessButtonInputs( m_pKeyboard );
}

//----------------------------------------------------------------------
IInputProfile* KeyboardProfile::CreateProfile( std::ifstream& fin, WkDeviceManagerPtr pInputDeviceMgr, WkActionTranslatorPtr pActionTransl, int& port ) 
{ 
	KeyboardProfile* NewProfile = new KeyboardProfile( pInputDeviceMgr ); 
	if( NewProfile->VInitialize( fin, pActionTransl ) )
	{
		return NewProfile;
	}
	SAFE_DELETE( NewProfile );
	return nullptr;
}