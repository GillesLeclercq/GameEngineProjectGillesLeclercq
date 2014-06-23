#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>

#include "IInputProfile.h"
#include "ButtonSet.h"
#include "ActionTranslator.h"
#include "Event_Action.h"

class ButtonProfile : virtual public IInputProfile
{
private:
	std::map<int, int> m_ButtonActionMap;
	std::set<int> m_ToggleButton;

public:
	ButtonProfile() {}
	virtual ~ButtonProfile() {}

	void MapButtonToAction( int button, int action ) { m_ButtonActionMap[ button ] = action; }
	std::string MapButtonToAction( ButtonSetPtr pDevice, ActionTranslatorPtr pActTransl, std::ifstream& fin );
	void ToggleButton( int button ) { m_ToggleButton.insert( button ); }

	bool IsToggle( int button ) const { return m_ToggleButton.find( button ) != m_ToggleButton.end(); }

	void ProcessButtonInputs( WkButtonSetPtr pDevice );
};