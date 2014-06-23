#pragma once

#include <set>
#include <memory>
#include <iostream>
#include <fstream>
#include <string>

#include "ActionTranslator.h"
#include "EventManager.h"

class IInputProfile
{
protected:
	std::set<int> m_GameObjectID;

	// Must be created through CreateProfile only for Initialization purpose.
	IInputProfile() {}
	virtual bool VInitialize( std::ifstream& fin, WkActionTranslatorPtr pActionTransl ) = 0;
	bool InitializeGOID( std::ifstream& fin );
	void SkipProfileInfo( std::ifstream& fin );

public:
	virtual ~IInputProfile() {}
	virtual void VProcessInput() = 0;
};

typedef std::shared_ptr<IInputProfile> InputProfilePtr;