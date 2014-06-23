#pragma once

#include <string>

class IInputSet
{
public:
	virtual int VStringToInputID( std::string& code ) = 0 ;
};