#pragma once

#include <iostream>
#include <d3d11_1.h>
#include <directxmath.h>

#include "IComponent.h"
#include "EventManager.h"
#include "Event_NewCurrentCamera.h"

struct PointLight
{
	DirectX::XMFLOAT4 m_Ambient;
	DirectX::XMFLOAT4 m_Diffuse;
	DirectX::XMFLOAT4 m_Specular;

	DirectX::XMFLOAT3 m_Position;
	float			  m_Range;

	DirectX::XMFLOAT3 m_Att;
	float			  m_Pad;
};

class PointLightContainer : public IComponent
{
private:
	static const unsigned long s_CompType = 0x62288ccf;

	PointLight*					m_pPointLight;			

public:
	PointLightContainer( GameObject* owner ): IComponent( owner ) {}
	~PointLightContainer() { SAFE_DELETE(m_pPointLight); }

	bool VInitialize( XmlMediator* pComponent ) override;
	const unsigned long& VGetComponentType() const { return s_CompType; }

	PointLight*	GetPointLight() { return m_pPointLight; }

	static const unsigned long& GetComponentType() { return s_CompType; }
	static IComponent* CreateComponent( GameObject* owner ) { return new PointLightContainer( owner ); }
};