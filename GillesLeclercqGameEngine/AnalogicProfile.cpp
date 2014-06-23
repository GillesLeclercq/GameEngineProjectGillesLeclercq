#include "AnalogicProfile.h"

using namespace std;

//----------------------------------------------------------------------
bool AnalogicProfile::MapAnalogicToAction( int button, int action )
{
	bool FreeInputID = ( m_AnalogicActionMap.find( button ) == m_AnalogicActionMap.end() );
	m_AnalogicActionMap[ button ] = action;
	return FreeInputID;
}

//----------------------------------------------------------------------
string AnalogicProfile::MapAnalogicToAction( AnalogicSetPtr pDevice, ActionTranslatorPtr pActTransl, std::ifstream& fin )
{
	string temp = "";
	int action = -1;
	int button = -1;

	// Map button to action
	fin >> temp;
	action = pActTransl->GetAction(temp);
	fin >> temp;
	button = pDevice->VStringToInputID( temp );
	MapAnalogicToAction( button, action );

	fin >> temp;

	return temp;
}

//----------------------------------------------------------------------
void AnalogicProfile::ProcessAnalogicInputs( WkAnalogicSetPtr pDeviceArg )
{
	if( auto pDevice = pDeviceArg.lock() )
	{
		for( auto Button : m_AnalogicActionMap )
		{
			float ButtonState = pDevice->Analogic_GetState( Button.first );
			if( ButtonState != 0.0f )
			{
				for( auto GO : m_GameObjectID )
				{
					EventManager::Instance().SendEvent( std::make_shared<Event_AnalogicAction>( GO, Button.second, ButtonState ) );
				}
			}
		}
	}
}