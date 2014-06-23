#pragma once

#include <iostream>
#include <map>

#include "TinyXml/tinyxml.h"

#include "XmlMediator.h"

class TinyXmlLoader
{
private:
	void _VisitXmlFile( TiXmlElement* pXmlRoot, XmlMediator* pMedRoot );

public:
	static TinyXmlLoader& Instance() { return s_Instance; }

	XmlMediator* LoadFile( const char* doc );

// Singleton
private:
	TinyXmlLoader( const TinyXmlLoader& )					{}
	TinyXmlLoader& operator=( const TinyXmlLoader& )		{}

	TinyXmlLoader()											{}
	~TinyXmlLoader()										{}

	static TinyXmlLoader s_Instance;
};