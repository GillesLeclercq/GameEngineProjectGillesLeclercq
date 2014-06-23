#include "TinyXmlLoader.h"

TinyXmlLoader TinyXmlLoader::s_Instance = TinyXmlLoader();

void TinyXmlLoader::_VisitXmlFile( TiXmlElement* pXmlRoot, XmlMediator* pMedRoot )
{
	TiXmlElement* pChild = pXmlRoot->FirstChildElement();

	if( pChild == nullptr )
	{
		pMedRoot->m_Content = pXmlRoot->GetText();
		return;
	}

	while( pChild != nullptr )
	{
		XmlMediator* pChildNode = new XmlMediator();
		pMedRoot->AddChild( std::string(pChild->Value()), pChildNode );
		_VisitXmlFile( pChild, pChildNode );

		pChild = pChild->NextSiblingElement();
	}
}

//----------------------------------------------------------------
// Keep the handle on file in the map
// Return the root of the file or nullptr if it can't be opened
XmlMediator* TinyXmlLoader::LoadFile( const char* file )
{
	TiXmlDocument doc( file );
	
	if( !doc.LoadFile() )
	{
		std::cerr << "Fail to load " << file << std::endl;
		return nullptr;
	}

	TiXmlElement* pRoot = doc.FirstChildElement();
	XmlMediator* result = new XmlMediator( std::string(pRoot->Value()) );

	_VisitXmlFile( pRoot, result );

	return result;
}
/*
TiXmlElement* XmlLoader::LoadFile( const char* file )
{
	auto findIt = m_HandleMap.find( file );
	if( findIt == m_HandleMap.end() )
	{
		TiXmlDocument* doc = new TiXmlDocument( file );
		if( doc->LoadFile() )
		{
			m_HandleMap[ file ] = doc;
			return doc->FirstChildElement();
		}
	}
	return nullptr;
}
*/