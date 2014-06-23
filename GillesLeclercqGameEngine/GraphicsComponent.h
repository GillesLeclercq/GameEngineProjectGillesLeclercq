#pragma once

#include <iostream>
#include <d3d11_1.h>
#include <directxmath.h>
#include "Effect\d3dx11effect.h"

#include "Mesh.h"
#include "Camera.h"

#include "IComponent.h"
#include "ILightManager.h"

class GraphicsComponent : public IComponent
{
private:
	static const unsigned long s_CompType = 0xd2386f83;

	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;

	ID3DX11EffectMatrixVariable* m_pEffectMatrixWorViewProj;
	ID3DX11EffectMatrixVariable* m_pEffectMatrixWorld;
	ID3DX11EffectMatrixVariable* m_pEffectMatrixView;
	ID3DX11EffectMatrixVariable* m_pEffectMatrixProj;
	ID3DX11EffectMatrixVariable* m_pEffectworldInvTrans;
	ID3DX11EffectMatrixVariable* m_pEffectTexTransform;
	ID3DX11EffectVariable* m_pEffectMaterial;
	ID3DX11EffectShaderResourceVariable* m_pEffectTextureVar;
	ID3DX11EffectVariable* m_pEffectEyePosition;
	ID3DX11EffectVariable* m_pEffectDirectionalLights;
	ID3DX11EffectVariable* m_pEffectPointLights;
	ID3DX11EffectVariable* m_pEffectSpotLights;

	ID3DX11EffectVariable* m_pEffectNbOfDirectionalLights;
	ID3DX11EffectVariable* m_pEffectNbOfPointLights;

public:
	GraphicsComponent( GameObject* owner ): IComponent( owner ) {}
	~GraphicsComponent();

	bool VInitialize( XmlMediator* pComponent ) override;

	bool InitializeBuffers(ID3D11Device* m_pD3dDevice);

	bool InitalizeEffects();

	void Draw(ID3D11DeviceContext* pImmediateContext, Camera* camera, ILightManager* pLightManager);

	const unsigned long& VGetComponentType() const { return s_CompType; }

	static const unsigned long& GetComponentType() { return s_CompType; }
	static IComponent* CreateComponent( GameObject* owner ) { return new GraphicsComponent( owner ); }
};