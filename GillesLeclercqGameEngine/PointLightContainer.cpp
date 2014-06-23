#include "PointLightContainer.h"
#include "GameObject.h"
#include <string>

using namespace std;
using namespace DirectX;

//----------------------------------------------------------------------
bool PointLightContainer::VInitialize( XmlMediator* pComponent )
{
	XmlMediator* pValueAmbient = pComponent->GetChildren((string)"Ambient").front();
	XmlMediator* pValueDiffuse = pComponent->GetChildren((string)"Diffuse").front();
	XmlMediator* pValueSpecular = pComponent->GetChildren((string)"Specular").front();
	XmlMediator* pValuePosition = pComponent->GetChildren((string)"Position").front();
	XmlMediator* pValueAtt = pComponent->GetChildren((string)"Att").front();

	PointLight* pointLight = new PointLight;

	pointLight->m_Ambient = XMFLOAT4((float)atof(pValueAmbient->GetChildren((string)"X").front()->GetContent().c_str()) ,
									 (float)atof(pValueAmbient->GetChildren((string)"Y").front()->GetContent().c_str()) ,
						             (float)atof(pValueAmbient->GetChildren((string)"Z").front()->GetContent().c_str()) ,
						             1.0);

	pointLight->m_Diffuse = XMFLOAT4((float)atof(pValueDiffuse->GetChildren((string)"X").front()->GetContent().c_str()) ,
									 (float)atof(pValueDiffuse->GetChildren((string)"Y").front()->GetContent().c_str()) ,
						             (float)atof(pValueDiffuse->GetChildren((string)"Z").front()->GetContent().c_str()) ,
						             1.0);

	pointLight->m_Specular = XMFLOAT4((float)atof(pValueSpecular->GetChildren((string)"X").front()->GetContent().c_str()) ,
									  (float)atof(pValueSpecular->GetChildren((string)"Y").front()->GetContent().c_str()) ,
						              (float)atof(pValueSpecular->GetChildren((string)"Z").front()->GetContent().c_str()) ,
						              (float)atof(pValueSpecular->GetChildren((string)"W").front()->GetContent().c_str()));


	pointLight->m_Position = XMFLOAT3((float)atof(pValuePosition->GetChildren((string)"X").front()->GetContent().c_str()) ,
								      (float)atof(pValuePosition->GetChildren((string)"Y").front()->GetContent().c_str()) ,
						              (float)atof(pValuePosition->GetChildren((string)"Z").front()->GetContent().c_str()));

	pointLight->m_Att = XMFLOAT3((float)atof(pValuePosition->GetChildren((string)"X").front()->GetContent().c_str()) ,
								 (float)atof(pValuePosition->GetChildren((string)"Y").front()->GetContent().c_str()) ,
						         (float)atof(pValuePosition->GetChildren((string)"Z").front()->GetContent().c_str()));

	pointLight->m_Range = (float)atof(pComponent->GetChildren((string)"Range").front()->GetContent().c_str());

	pointLight->m_Pad = 1.0;

	m_pPointLight = pointLight;

	return true;
}
