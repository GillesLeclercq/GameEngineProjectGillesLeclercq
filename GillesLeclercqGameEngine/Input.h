#pragma once

#include <map>
#include <iostream>
#include <fstream>
#include "FastDelegate\FastDelegate.h"

#include "Utilities.h"

#include "GameObjectManager.h"

#include "InputDeviceManager.h"
#include "TestInputComponent.h"

#include "IInputProfile.h"
#include "KeyboardProfile.h"
#include "XInputProfile.h"
#include "ActionTranslator.h"

typedef IInputProfile* (*ProfileCreator)( std::ifstream&, WkDeviceManagerPtr, WkActionTranslatorPtr, int& );
typedef std::map<std::string, ProfileCreator> ProfileCreatorMap;

class Input
{
private:
	DeviceManagerPtr m_pDeviceManager;
	ActionTranslatorPtr m_pActionTranslator;

	ProfileCreatorMap m_pProfileCreators;

	std::set<InputProfilePtr> m_pInputProfiles;

public:
	Input() {}
	~Input() {}

	bool Initialize( GameObjectManager* pGOManager );
	bool RegisterProfileCreator( std::string keyword, ProfileCreator func );
	bool InitializeProfiles( std::ifstream& ProfileFile );

	void OnKeyDown( const char& key );
	void OnKeyUp( const char& key );

	void ProcessInputs();
};