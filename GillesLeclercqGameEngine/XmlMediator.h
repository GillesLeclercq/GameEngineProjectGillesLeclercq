#pragma once

#include <map>
#include <list>
#include <string>

#include "Utilities.h"

class XmlMediator
{
	friend class TinyXmlLoader;

private:
	std::string										m_Content;
	std::map<std::string, std::list<XmlMediator*>>	m_Children;

public:
	XmlMediator( std::string content = "" ): m_Content( content ) {}
	~XmlMediator();

	void AddChild( std::string& childDesc, XmlMediator* child );

	std::map<std::string, std::list<XmlMediator*>> GetAllChildren() const { return m_Children; }
	std::list<XmlMediator*> GetChildren( std::string& childDesc ) const;
	std::string GetContent() const { return m_Content; }

	int DeleteChildren( std::string key );
};