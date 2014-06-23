#include "KeyboardDevice.h"

std::map<std::string, int> KeyboardDevice::s_StrToID;

//----------------------------------------------------------------------
KeyboardDevice::KeyboardDevice(): ButtonSet(256) 
{
	if( s_StrToID.empty() )
	{
		s_StrToID["back"] = 8;		s_StrToID["tab"] = 9;		s_StrToID["return"] = 13;
		s_StrToID["shift"] = 16;	s_StrToID["ctrl"] = 17;		s_StrToID["control"] = 17;
		s_StrToID["alt"] = 18;		s_StrToID["capslock"] = 20;	s_StrToID["escape"] = 27;
		s_StrToID["esc"] = 27;		s_StrToID["space"] = 32;	s_StrToID["left"] = 37;
		s_StrToID["up"] = 38;		s_StrToID["right"] = 39;	s_StrToID["down"] = 40;
	}
}

//----------------------------------------------------------------------
// Check if code is a simple letter => Return ASCII code (in upper case).
// Check if it is a special key.
// Check if it is [0-9].
// Returns -1 is not recognized.
int KeyboardDevice::VStringToInputID( std::string& code )
{
	if( code.size() == 1 ) // Is it a letter?
	{
		return (*(code.c_str()))-32;
	}

	auto findIt = s_StrToID.find( code );
	if( findIt != s_StrToID.end() ) // Is it a special key?
	{
		return findIt->second;
	}

	int nb = -1;
	nb = atoi(code.c_str());
	if( -1 < nb && nb < 10 ) // Is it a number?
	{
		return nb + 48;
	}

	return -1;
}