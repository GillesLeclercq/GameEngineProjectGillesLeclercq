#include "DirectionalLightContainer.h"
#include "GameObject.h"
#include <string>

using namespace std;
using namespace DirectX;

//----------------------------------------------------------------------
bool DirectionalLightContainer::VInitialize( XmlMediator* pComponent )
{
	XmlMediator* pValueAmbient = pComponent->GetChildren((string)"Ambient").front();
	XmlMediator* pValueDiffuse = pComponent->GetChildren((string)"Diffuse").front();
	XmlMediator* pValueSpecular = pComponent->GetChildren((string)"Specular").front();
	XmlMediator* pValueDirection = pComponent->GetChildren((string)"Direction").front();

	DirectionalLight* directionalLight = new DirectionalLight;

	directionalLight->m_Ambient = XMFLOAT4((float)atof(pValueAmbient->GetChildren((string)"X").front()->GetContent().c_str()) ,
										   (float)atof(pValueAmbient->GetChildren((string)"Y").front()->GetContent().c_str()) ,
						                   (float)atof(pValueAmbient->GetChildren((string)"Z").front()->GetContent().c_str()) ,
						                   1.0);

	directionalLight->m_Diffuse = XMFLOAT4((float)atof(pValueDiffuse->GetChildren((string)"X").front()->GetContent().c_str()) ,
										   (float)atof(pValueDiffuse->GetChildren((string)"Y").front()->GetContent().c_str()) ,
						                   (float)atof(pValueDiffuse->GetChildren((string)"Z").front()->GetContent().c_str()) ,
						                   1.0);

	directionalLight->m_Specular = XMFLOAT4((float)atof(pValueSpecular->GetChildren((string)"X").front()->GetContent().c_str()) ,
										    (float)atof(pValueSpecular->GetChildren((string)"Y").front()->GetContent().c_str()) ,
						                    (float)atof(pValueSpecular->GetChildren((string)"Z").front()->GetContent().c_str()) ,
						                    (float)atof(pValueSpecular->GetChildren((string)"W").front()->GetContent().c_str()));


	directionalLight->m_Direction = XMFLOAT3((float)atof(pValueDirection->GetChildren((string)"X").front()->GetContent().c_str()) ,
										     (float)atof(pValueDirection->GetChildren((string)"Y").front()->GetContent().c_str()) ,
						                     (float)atof(pValueDirection->GetChildren((string)"Z").front()->GetContent().c_str()));

	directionalLight->m_Pad = 1.0;

	m_pDirectionalLight = directionalLight;

	return true;
}
