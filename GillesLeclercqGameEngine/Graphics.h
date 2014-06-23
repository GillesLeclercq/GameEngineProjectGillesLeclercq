#pragma once

#include <iostream>
#include <map>
#include <d3d11_1.h>
#include <directxmath.h>
#include <directxcolors.h>

#include "IGraphics.h"
#include "IComponent.h"
#include "Camera.h"
#include "ILightManager.h"

#include "Event_LookForDevices.h"
#include "Event_CreateShader.h"
#include "Event_NewCurrentCamera.h"


class Graphics : public IGraphics
{
public:
	Graphics() {}
	~Graphics();

	bool VInitialize( GameObjectManager* goManager ) override;
	void VDraw() override;

	int CreateGraphics(IEventPtr evt);

	void SendBackDevice(IEventPtr evt);

	void ReceiveNewCurrentCamera(IEventPtr evt);

	void SetLightManager(ILightManager* pLightManager) { m_pLightManager = pLightManager; }

private:

	D3D_DRIVER_TYPE         m_DriverType;
	D3D_FEATURE_LEVEL       m_FeatureLevel;
	ID3D11Device*           m_pD3dDevice;
	ID3D11DeviceContext*    m_pImmediateContext;
	IDXGISwapChain*         m_pSwapChain;
	ID3D11RenderTargetView* m_pRenderTargetView;
	ID3D11DepthStencilView* m_pDepthStencilView;
	ID3D11Texture2D*        m_pDepthStencil;
	ID3D11InputLayout*      m_pVertexLayout;

	Camera*					m_pCurrentCamera;
	ILightManager*			m_pLightManager;

};