#include "Transformation.h"

#include "GameObject.h"

using namespace std;
using namespace DirectX;

bool Transformation::VInitialize( XmlMediator* pComponent )
{

	XmlMediator* pValuePosition = pComponent->GetChildren((string)"Position").front();
	XmlMediator* pValueRotation = pComponent->GetChildren((string)"Rotation").front();
	XmlMediator* pValueScale = pComponent->GetChildren((string)"Scale").front();

	m_pOwner->RegisterUpdateMethod( GetComponentType(), fastdelegate::MakeDelegate( this, &Transformation::Update ) );


	m_Position.x = (float)atof(pValuePosition->GetChildren((string)"X").front()->GetContent().c_str());
	m_Position.y = (float)atof(pValuePosition->GetChildren((string)"Y").front()->GetContent().c_str());
	m_Position.z = (float)atof(pValuePosition->GetChildren((string)"Z").front()->GetContent().c_str());

	m_Rotation.x = (float)atof(pValueRotation->GetChildren((string)"X").front()->GetContent().c_str());
	m_Rotation.y = (float)atof(pValueRotation->GetChildren((string)"Y").front()->GetContent().c_str());
	m_Rotation.z = (float)atof(pValueRotation->GetChildren((string)"Z").front()->GetContent().c_str());

	m_Scale.x = (float)atof(pValueScale->GetChildren((string)"X").front()->GetContent().c_str());
	m_Scale.y = (float)atof(pValueScale->GetChildren((string)"Y").front()->GetContent().c_str());
	m_Scale.z = (float)atof(pValueScale->GetChildren((string)"Z").front()->GetContent().c_str());

	m_pOwner->RegisterGetMethod( "GetPosition", (GetMethod&) fastdelegate::MakeDelegate( this, &Transformation::GetPosition ) );
	m_pOwner->RegisterGetMethod( "GetRotation", (GetMethod&) fastdelegate::MakeDelegate( this, &Transformation::GetRotation ) );
	m_pOwner->RegisterGetMethod( "GetScale", (GetMethod&) fastdelegate::MakeDelegate( this, &Transformation::GetScale ) );

	m_pOwner->RegisterGetMethod( "GetmWorld", (GetMethod&) fastdelegate::MakeDelegate( this, &Transformation::GetmWorld ) );

	XMMATRIX translate = XMMatrixTranslation(m_Position.x, m_Position.y ,m_Position.z);
	XMMATRIX scale = XMMatrixScaling(m_Scale.x, m_Scale.y ,m_Scale.z);
	XMMATRIX rotateX = XMMatrixRotationX(m_Rotation.x);
	XMMATRIX rotateY = XMMatrixRotationY(m_Rotation.y);
	XMMATRIX rotateZ = XMMatrixRotationZ(m_Rotation.z);

	XMMATRIX worldtmp = scale*rotateX*rotateY*rotateZ*translate;

	XMStoreFloat4x4(&m_World,worldtmp);

	return true;
}

void Transformation::Update( float& frameTime )
{
	
	XMMATRIX translate = XMMatrixTranslation(m_Position.x, m_Position.y ,m_Position.z);
	XMMATRIX scale = XMMatrixScaling(m_Scale.x, m_Scale.y ,m_Scale.z);
	XMMATRIX rotateX = XMMatrixRotationX(m_Rotation.x);
	XMMATRIX rotateY = XMMatrixRotationY(m_Rotation.y);
	XMMATRIX rotateZ = XMMatrixRotationZ(m_Rotation.z);

	XMMATRIX worldtmp = scale*rotateX*rotateY*rotateZ*translate;

	XMStoreFloat4x4(&m_World,worldtmp);
}