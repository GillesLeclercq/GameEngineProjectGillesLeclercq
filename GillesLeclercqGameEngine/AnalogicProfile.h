#pragma once

#include <map>

#include "IInputProfile.h"
#include "AnalogicSet.h"
#include "ActionTranslator.h"
#include "Event_AnalogicAction.h"

class AnalogicProfile : virtual public IInputProfile
{
private:
	std::map<int, int> m_AnalogicActionMap;

public:
	AnalogicProfile() {}
	virtual ~AnalogicProfile() {}

	bool MapAnalogicToAction( int button, int action );
	std::string MapAnalogicToAction( AnalogicSetPtr pDevice, ActionTranslatorPtr pActTransl, std::ifstream& fin );

	void ProcessAnalogicInputs( WkAnalogicSetPtr pDeviceArg );
};