#pragma once

#include <iostream>
#include <d3d11_1.h>
#include <directxmath.h>

#include "IComponent.h"
#include "EventManager.h"
#include "Event_NewCurrentCamera.h"

class Camera : public IComponent
{
private:
	static const unsigned long s_CompType = 0xe92a0419;

	DirectX::XMFLOAT3 m_Position;
	DirectX::XMFLOAT3 m_Right;
	DirectX::XMFLOAT3 m_Up;
	DirectX::XMFLOAT3 m_Look;

	float m_NearZ;
	float m_FarZ;
	float m_Aspect;
	float m_FovY;

	float m_AnglePitch;

	DirectX::XMFLOAT4X4 m_View;
	DirectX::XMFLOAT4X4 m_Proj;

	bool m_CurrentCamera;

public:
	Camera( GameObject* owner ): IComponent( owner ) {}
	~Camera() {}

	void SetCurrentCamera (bool currentCamera) { m_CurrentCamera = currentCamera ; }

	void Update( float& frameTime );

	bool VInitialize( XmlMediator* pComponent ) override;
	const unsigned long& VGetComponentType() const { return s_CompType; }

	DirectX::XMFLOAT4X4 GetViewMatrix() { return m_View; }
	DirectX::XMFLOAT4X4 GetProjMatrix() { return m_Proj; }

	DirectX::XMFLOAT3 GetPosition() { return m_Position; }

	static const unsigned long& GetComponentType() { return s_CompType; }
	static IComponent* CreateComponent( GameObject* owner ) { return new Camera( owner ); }
};
