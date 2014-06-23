#pragma once

#include <string>

class IScriptManager
{
	virtual bool VInitialize() = 0;
	virtual bool VExecuteFile( const char* file ) = 0;
	virtual bool VExecuteString( const char* cmd ) = 0;
};