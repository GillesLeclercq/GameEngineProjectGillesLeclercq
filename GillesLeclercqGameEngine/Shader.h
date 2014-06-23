#pragma once
#include <iostream>
#include "Effect/d3dx11effect.h"
#include <d3dcompiler.h>
#include <directxmath.h>
#include "IComponent.h"

class Shader : public IComponent
{

private:
	ID3DX11Effect*				m_pFx;
	ID3DX11EffectTechnique*		m_pTech;

	std::string					m_ShaderFilename;
	std::string					m_TechniqueName;
	std::string					m_Target;

	static const unsigned long	s_CompType = 0x68fef6f3;

public:
	Shader( GameObject* owner ) : IComponent( owner ) {}

	bool VInitialize( XmlMediator* pComponent ) override;
	const unsigned long& VGetComponentType() const { return s_CompType; }

	void* GetTechnique() { return (void*)&m_pTech; } 
	void* GetEffect() const { 
		return (void*)&m_pFx ; 
	};

	static const unsigned long& GetComponentType() { return s_CompType; }
	static IComponent* CreateComponent( GameObject* owner ) { return new Shader( owner ); }

	void InitShader(ID3D11Device* device, ID3D11DeviceContext* pImmediateContext, ID3D11InputLayout** pVertexLayout);


};
