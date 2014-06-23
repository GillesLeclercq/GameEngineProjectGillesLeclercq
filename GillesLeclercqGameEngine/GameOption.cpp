#include "GameOption.h"

using namespace std;

//----------------------------------------------------------------------
bool GameOption::LoadOptions(string fileName)
{

	XmlMediator* xmlMediator = TinyXmlLoader::Instance().LoadFile(fileName.c_str()); //ERROR CODE TO DO
	if (!xmlMediator)
		return false;

	auto resultWidth = xmlMediator->GetChildren((string)"Width");
	if (resultWidth.size() != 1)
		return false;
	SetWidth(stoi(resultWidth.front()->GetContent()));

	auto resultLength = xmlMediator->GetChildren((string)"Length");
	if (resultLength.size() != 1)
		return false;
	SetLength(stoi(resultLength.front()->GetContent()));

	auto resultFullscreen= xmlMediator->GetChildren((string)"Fullscreen");
	if (resultFullscreen.size() != 1)
		return false;
	if (resultFullscreen.front()->GetContent() == "true")
		SetFullscreen(true);
	else if (resultFullscreen.front()->GetContent() == "false")
		SetFullscreen(false);
	else
		return false;

	return true;
}