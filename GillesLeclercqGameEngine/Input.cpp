#include "Input.h"

using namespace std;

//----------------------------------------------------------------------
bool Input::Initialize( GameObjectManager* pGOManager )
{
	m_pDeviceManager.reset( new InputDeviceManager() );
	m_pDeviceManager->RefreshControllers();

	ifstream fin( "ActionDesc.txt" );
	if( fin.is_open() )
	{
		m_pActionTranslator.reset( new ActionTranslator( fin ) );
		fin.close();
	}
	IInputComponent::s_pActionTranslator = WkActionTranslatorPtr( m_pActionTranslator );

	pGOManager->RegisterComponentCreator( "TestInputComponent", &TestInputComponent::CreateComponent );

	RegisterProfileCreator( "keyboard", &KeyboardProfile::CreateProfile );
	RegisterProfileCreator( "xinput", &XInputProfile::CreateProfile );

	return true;
}

//----------------------------------------------------------------------
bool Input::RegisterProfileCreator( std::string keyword, ProfileCreator func )
{
	bool findIt = ( m_pProfileCreators.find( keyword ) == m_pProfileCreators.end() );
	if( !findIt )
	{
		cout << "[Input] ProfileCreator already associated with " << keyword << ". Overwritting." << endl;
	}
	m_pProfileCreators[keyword] = func;
	return findIt;
}

//----------------------------------------------------------------------
bool Input::InitializeProfiles( ifstream& ProfileStream )
{
	string str = "";

	string DeviceType = "";
	string ActionStr = "";
	int InputID = -1, ActionID = -1;

	while( ProfileStream >> str )
	{
		auto keywords = StringUtilities::Split( StringUtilities::ToLower(str), '_' );
		string deviceType = keywords.at(0);
		int port = -1;
		if( keywords.size() > 1 )
		{
			port = atoi( keywords.at(1).c_str() );
		}
		auto findIt = m_pProfileCreators.find(deviceType);
		if( findIt != m_pProfileCreators.end() )
		{
			IInputProfile* newProfile = findIt->second( ProfileStream, WkDeviceManagerPtr(m_pDeviceManager), WkActionTranslatorPtr(m_pActionTranslator), port );
			if( newProfile != nullptr )
			{
				InputProfilePtr newProfPtr = InputProfilePtr( newProfile );
				m_pInputProfiles.insert( newProfPtr );
			}
		}
		else
		{
			cout << "[Input] Profile loading failed. " << str << " profile type unknown." << endl;
			return false;
		}
		
	}
	return true;
}

//----------------------------------------------------------------------
void Input::OnKeyDown( const char& key )
{
	if( auto keyboard = m_pDeviceManager->GetKeyboard().lock() )
	{
		keyboard->Button_OnKeyDown(key);
	}
}
	
//----------------------------------------------------------------------
void Input::OnKeyUp( const char& key )
{
	if( auto keyboard = m_pDeviceManager->GetKeyboard().lock() )
	{
		keyboard->Button_OnKeyUp(key);
	}
}

//----------------------------------------------------------------------
void Input::ProcessInputs()
{
	m_pDeviceManager->RefreshControllers();

	for( auto it = m_pInputProfiles.begin(); it!=m_pInputProfiles.end(); it++ )
	{
		(*it)->VProcessInput();
	}
}