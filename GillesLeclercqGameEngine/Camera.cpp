#include "Camera.h"
#include "GameObject.h"

using namespace std;
using namespace DirectX;

//----------------------------------------------------------------------
bool Camera::VInitialize( XmlMediator* pComponent )
{

	m_pOwner->RegisterUpdateMethod( GetComponentType(), fastdelegate::MakeDelegate( this, &Camera::Update ) );

	auto pValuePositon = pComponent->GetChildren((string)"Position").front();
	auto pRight = pComponent->GetChildren((string)"Right").front();
	auto pUp = pComponent->GetChildren((string)"Up").front();
	auto pLook = pComponent->GetChildren((string)"Look").front();

	m_Position.x = (float)atof(pValuePositon->GetChildren((string)"X").front()->GetContent().c_str());
	m_Position.y = (float)atof(pValuePositon->GetChildren((string)"Y").front()->GetContent().c_str());
	m_Position.z = (float)atof(pValuePositon->GetChildren((string)"Z").front()->GetContent().c_str());

	m_Right.x = (float)atof(pRight->GetChildren((string)"X").front()->GetContent().c_str());
	m_Right.y = (float)atof(pRight->GetChildren((string)"Y").front()->GetContent().c_str());
	m_Right.z = (float)atof(pRight->GetChildren((string)"Z").front()->GetContent().c_str());

	m_Up.x = (float)atof(pUp->GetChildren((string)"X").front()->GetContent().c_str());
	m_Up.y = (float)atof(pUp->GetChildren((string)"Y").front()->GetContent().c_str());
	m_Up.z = (float)atof(pUp->GetChildren((string)"Z").front()->GetContent().c_str());

	m_Look.x = (float)atof(pLook->GetChildren((string)"X").front()->GetContent().c_str());
	m_Look.y = (float)atof(pLook->GetChildren((string)"Y").front()->GetContent().c_str());
	m_Look.z = (float)atof(pLook->GetChildren((string)"Z").front()->GetContent().c_str());

	m_NearZ = (float)atof(pComponent->GetChildren((string)"NearZ").front()->GetContent().c_str());
	m_FarZ = (float)atof(pComponent->GetChildren((string)"FarZ").front()->GetContent().c_str());
	m_Aspect = (float)atof(pComponent->GetChildren((string)"Aspect").front()->GetContent().c_str());
	m_FovY = (float)atof(pComponent->GetChildren((string)"FovY").front()->GetContent().c_str());

	m_AnglePitch = (float)atof(pComponent->GetChildren((string)"AnglePitch").front()->GetContent().c_str());

	XMVECTOR R = XMLoadFloat3(&m_Right);
	XMVECTOR U = XMLoadFloat3(&m_Up);
	XMVECTOR L = XMLoadFloat3(&m_Look);
	XMVECTOR P = XMLoadFloat3(&m_Position);

	L = XMVector3Normalize(L);
	U = XMVector3Normalize(XMVector3Cross(L, R));

	R = XMVector3Cross(U, L); 

	float x = -XMVectorGetX(XMVector3Dot(P, R));
	float y = -XMVectorGetX(XMVector3Dot(P, U));
	float z = -XMVectorGetX(XMVector3Dot(P, L));

	XMStoreFloat3(&m_Right, R);
	XMStoreFloat3(&m_Up, U);
	XMStoreFloat3(&m_Look, L);

	m_View(0,0) = m_Right.x; 
	m_View(1,0) = m_Right.y; 
	m_View(2,0) = m_Right.z; 
	m_View(3,0) = x;   

	m_View(0,1) = m_Up.x;
	m_View(1,1) = m_Up.y;
	m_View(2,1) = m_Up.z;
	m_View(3,1) = y;  

	m_View(0,2) = m_Look.x; 
	m_View(1,2) = m_Look.y; 
	m_View(2,2) = m_Look.z; 
	m_View(3,2) = z;   

	m_View(0,3) = 0.0f;
	m_View(1,3) = 0.0f;
	m_View(2,3) = 0.0f;
	m_View(3,3) = 1.0f;

	XMMATRIX Proj = XMMatrixPerspectiveFovLH(m_FovY, m_Aspect, m_NearZ, m_FarZ);
	XMStoreFloat4x4(&m_Proj, Proj);

	string currentCamera = pComponent->GetChildren((string)"CurrentCamera").front()->GetContent();
	if (currentCamera == "true")
	{
		EventManager::Instance().SendEvent ( 
			std::make_shared<Event_NewCurrentCamera>(
				Event_NewCurrentCamera(m_pOwner->GetID(), this)));
		m_CurrentCamera = true;
	}
	else
	{
		m_CurrentCamera = false;
	}


	return true;
}

void Camera::Update( float& frameTime )
{
	
	XMVECTOR R = XMLoadFloat3(&m_Right);
	XMVECTOR U = XMLoadFloat3(&m_Up);
	XMVECTOR L = XMLoadFloat3(&m_Look);
	XMVECTOR P = XMLoadFloat3(&m_Position);

	L = XMVector3Normalize(L);
	U = XMVector3Normalize(XMVector3Cross(L, R));

	R = XMVector3Cross(U, L); 

	float x = -XMVectorGetX(XMVector3Dot(P, R));
	float y = -XMVectorGetX(XMVector3Dot(P, U));
	float z = -XMVectorGetX(XMVector3Dot(P, L));

	XMStoreFloat3(&m_Right, R);
	XMStoreFloat3(&m_Up, U);
	XMStoreFloat3(&m_Look, L);

	m_View(0,0) = m_Right.x; 
	m_View(1,0) = m_Right.y; 
	m_View(2,0) = m_Right.z; 
	m_View(3,0) = x;   

	m_View(0,1) = m_Up.x;
	m_View(1,1) = m_Up.y;
	m_View(2,1) = m_Up.z;
	m_View(3,1) = y;  

	m_View(0,2) = m_Look.x; 
	m_View(1,2) = m_Look.y; 
	m_View(2,2) = m_Look.z; 
	m_View(3,2) = z;   

	m_View(0,3) = 0.0f;
	m_View(1,3) = 0.0f;
	m_View(2,3) = 0.0f;
	m_View(3,3) = 1.0f;

	XMMATRIX Proj = XMMatrixPerspectiveFovLH(m_FovY, m_Aspect, m_NearZ, m_FarZ);
	XMStoreFloat4x4(&m_Proj, Proj);

}