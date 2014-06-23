#include "ActionTranslator.h"

using namespace std;

//----------------------------------------------------------------------
ActionTranslator::ActionTranslator( ifstream& actionFile )
{
	string tmp = "";
	string actionStr = "";
	int actionInt = -1;

	while( actionFile >> tmp )
	{
		actionStr = StringUtilities::ToLower( tmp );
		
		actionFile >> tmp;
		actionInt = atoi( tmp.c_str() );

		m_StrToActionMap[ actionStr ] = (ACTION)actionInt;
	}
}

//----------------------------------------------------------------------
int ActionTranslator::GetAction( string word )
{
	auto findIt = m_StrToActionMap.find( StringUtilities::ToLower(word) );
	if( findIt != m_StrToActionMap.end() )
	{
		return findIt->second;
	}
	return -1;
}