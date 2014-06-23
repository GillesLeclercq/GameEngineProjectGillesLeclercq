#pragma once

#include "IEvent.h"
#include <d3d11_1.h>

class Event_CreateShader : public IEvent
{
private:
	
	ID3D11Device*			m_pD3dDevice;
	ID3D11DeviceContext*    m_pImmediateContext;
	ID3D11InputLayout**		m_pVertexLayout;

	static const unsigned long s_EvtType = 0xac3666bc;
public:
	Event_CreateShader( ID3D11Device* pD3dDevice, ID3D11DeviceContext* pImmediateContext, ID3D11InputLayout** pVertexLayout): 
		m_pD3dDevice( pD3dDevice ), m_pImmediateContext( pImmediateContext ), m_pVertexLayout( pVertexLayout ) { } ;

	ID3D11Device* GetDevice() const { return m_pD3dDevice; }
	ID3D11DeviceContext* GetImmediateContext() const { return m_pImmediateContext; }
	ID3D11InputLayout** GetVertexLayout() const { return m_pVertexLayout; }

	virtual unsigned long VGetEvtType() const override { return s_EvtType; }

	static const unsigned long& EventType() { return s_EvtType; }

};

