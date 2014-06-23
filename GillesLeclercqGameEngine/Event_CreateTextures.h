#pragma once

#include "IEvent.h"
#include <d3d11_1.h>


class Event_CreateTextures : public IEvent
{
private:
	
	ID3D11Device*			m_pD3dDevice;

	static const unsigned long s_EvtType = 0x1f679b87;
public:
	Event_CreateTextures( ID3D11Device* d3dDevice): 
		m_pD3dDevice( d3dDevice ) { } ;

	ID3D11Device* GetD3dDevice() const { return m_pD3dDevice; }

	virtual unsigned long VGetEvtType() const override { return s_EvtType; }

	static const unsigned long& EventType() { return s_EvtType; }

};
