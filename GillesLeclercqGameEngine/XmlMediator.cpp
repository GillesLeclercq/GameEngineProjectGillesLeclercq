#include "XmlMediator.h"

//-----------------------------------------------------------
XmlMediator::~XmlMediator()
{
	for( auto childDesc : m_Children )
	{
		for( auto child : childDesc.second )
		{
			SAFE_DELETE( child );
		}
	}
}

//-----------------------------------------------------------
void XmlMediator::AddChild( std::string& childDesc, XmlMediator* child )
{
	auto findIt = m_Children.find( childDesc );
	m_Children[ childDesc ].push_front( child );
}

//-----------------------------------------------------------
std::list<XmlMediator*> XmlMediator::GetChildren( std::string& childDesc ) const
{
	auto findIt = m_Children.find( childDesc );
	if( findIt != m_Children.end() )
	{
		return findIt->second;
	}
	return std::list<XmlMediator*>();
}

//-----------------------------------------------------------
// Returns the number of deleted branches.
int XmlMediator::DeleteChildren( std::string key )
{
	int Res = 0;
	auto findIt = m_Children.find( key );
	if( findIt != m_Children.end() && !findIt->second.empty() )
	{
		Res = findIt->second.size();
		for( auto child : findIt->second )
		{
			SAFE_DELETE( child );
		}
		m_Children.erase( findIt );
	}
	return Res;
}