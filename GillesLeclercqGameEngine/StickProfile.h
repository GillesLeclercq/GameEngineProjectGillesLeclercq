#pragma once

#include "IInputProfile.h"
#include "StickSet.h"
#include "ActionTranslator.h"
#include "Event_StickAction.h"

class StickProfile : virtual public IInputProfile
{
private:
	std::map<int, int> m_StickActionMap;

public:
	StickProfile() {}
	virtual ~StickProfile() {}

	bool MapStickToAction( int button, int action );
	std::string MapStickToAction( StickSetPtr pDevice, ActionTranslatorPtr pActTransl, std::ifstream& fin );

	void ProcessStickInputs( WkStickSetPtr pDeviceArg );
};