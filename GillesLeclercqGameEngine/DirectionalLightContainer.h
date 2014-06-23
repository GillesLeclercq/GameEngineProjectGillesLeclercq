#pragma once

#include <iostream>
#include <d3d11_1.h>
#include <directxmath.h>

#include "IComponent.h"
#include "EventManager.h"
#include "Event_NewCurrentCamera.h"

struct DirectionalLight
{
	DirectX::XMFLOAT4 m_Ambient;
	DirectX::XMFLOAT4 m_Diffuse;
	DirectX::XMFLOAT4 m_Specular;
	DirectX::XMFLOAT3 m_Direction;
	float			  m_Pad;
};

class DirectionalLightContainer : public IComponent
{
private:
	static const unsigned long s_CompType = 0x62288ccf;

	DirectionalLight*	m_pDirectionalLight;


public:
	DirectionalLightContainer( GameObject* owner ): IComponent( owner ) {}
	~DirectionalLightContainer() { SAFE_DELETE(m_pDirectionalLight);}

	bool VInitialize( XmlMediator* pComponent ) override;
	const unsigned long& VGetComponentType() const { return s_CompType; }

	DirectionalLight*	GetDirectionalLight() { return m_pDirectionalLight; }

	static const unsigned long& GetComponentType() { return s_CompType; }
	static IComponent* CreateComponent( GameObject* owner ) { return new DirectionalLightContainer( owner ); }
};