#include "StickProfile.h"

using namespace std;

//----------------------------------------------------------------------
bool StickProfile::MapStickToAction( int button, int action )
{
	bool FreeInputID = ( m_StickActionMap.find( button ) == m_StickActionMap.end() );
	m_StickActionMap[ button ] = action;
	return FreeInputID;
}

//----------------------------------------------------------------------
string StickProfile::MapStickToAction( StickSetPtr pDevice, ActionTranslatorPtr pActTransl, std::ifstream& fin )
{
	string temp = "";
	int action = -1;
	int button = -1;

	// Map button to action
	fin >> temp;
	action = pActTransl->GetAction(temp);
	fin >> temp;
	button = pDevice->VStringToInputID( temp );
	if( button > -1 )
	{
		MapStickToAction( button, action );
	}

	fin >> temp;

	return temp;
}

//----------------------------------------------------------------------
void StickProfile::ProcessStickInputs( WkStickSetPtr pDeviceArg )
{
	if( auto pDevice = pDeviceArg.lock() )
	{
		for( auto Stick : m_StickActionMap )
		{
			std::pair<float, float> StickState = pDevice->Stick_GetState( Stick.first );
			if( StickState.second != 0.0f || StickState.first != 0.0f )
			{
				for( auto GO : m_GameObjectID )
				{
					EventManager::Instance().SendEvent( std::make_shared<Event_StickAction>( GO, Stick.second, StickState ) );
				}
			}
		}
	}
}