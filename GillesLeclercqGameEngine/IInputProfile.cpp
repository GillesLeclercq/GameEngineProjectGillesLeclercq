#include "IInputProfile.h"

using namespace std;

//----------------------------------------------------------------------
bool IInputProfile::InitializeGOID( std::ifstream& fin )
{
	if( fin.is_open() )
	{
		string temp;

		// Setting the targeted GO
		int TargetsNb = 0;
		fin >> temp;
		TargetsNb = atoi(temp.c_str());
		for( int i = 0; i<TargetsNb; i++ )
		{
			fin >> temp;
			m_GameObjectID.insert( atoi(temp.c_str()) );
		}
		return true;
	}
	return false;
}

//----------------------------------------------------------------------
void IInputProfile::SkipProfileInfo( std::ifstream& fin )
{
	string temp = "";
	if( fin.is_open() )
	do 
	{
		fin >> temp;
	} 
	while( temp != ";" );
}