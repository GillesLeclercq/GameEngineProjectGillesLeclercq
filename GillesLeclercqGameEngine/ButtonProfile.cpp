#include "ButtonProfile.h"

using namespace std;

//----------------------------------------------------------------------
string ButtonProfile::MapButtonToAction( ButtonSetPtr pDevice, ActionTranslatorPtr pActTransl, std::ifstream& fin )
{
	string temp = "";
	int action = -1;
	int button = -1;

	// Map button to action
	fin >> temp;
	action = pActTransl->GetAction(temp);
	fin >> temp;
	button = pDevice->VStringToInputID( temp );
	if( button > -1 ) // Button recognized?
	{
		MapButtonToAction( button, action );
	}

	// Check if button is toggled
	fin >> temp;
	if( StringUtilities::ToLower(temp) == "t" )
	{
		if( button > -1 ) // Button recognized?
		{
			ToggleButton(button);
		}
		fin >> temp;
	}

	return temp;
}

//----------------------------------------------------------------------
void ButtonProfile::ProcessButtonInputs( WkButtonSetPtr pDeviceArg )
{
	if( auto pDevice = pDeviceArg.lock() )
	{
		for( auto Button : m_ButtonActionMap )
		{
			if( ( IsToggle( Button.first ) && pDevice->Button_IsPressed( Button.first ) )
				|| ( !IsToggle( Button.first ) && pDevice->Button_IsDown( Button.first ) ) )
			{
				for( auto GO : m_GameObjectID )
				{
					EventManager::Instance().SendEvent( make_shared<Event_Action>( GO, Button.second ) );
				}
			}
		}
	}
}