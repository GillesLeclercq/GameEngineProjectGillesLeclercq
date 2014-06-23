#pragma once
#include "icomponent.h"
#include <d3d11.h>
#include <directxmath.h>

#include "EventManager.h"

class Transformation :
	public IComponent
{
private:
	static const unsigned long s_CompType = 0x6518ad4b;

	DirectX::XMFLOAT3 m_Position;
	DirectX::XMFLOAT3 m_Rotation;
	DirectX::XMFLOAT3 m_Scale;

	DirectX::XMFLOAT4X4 m_World;


public:

	Transformation( GameObject* pOwner ) : IComponent( pOwner ), m_Position( 0.0f, 0.0f, 0.0f ),
																 m_Rotation( 0.0f, 0.0f, 0.0f ),
																 m_Scale( 1.0f, 1.0f, 1.0f) {}
	~Transformation() {};

	bool VInitialize( XmlMediator* pComponent ) override;

	void Update( float& frameTime );

	const unsigned long& VGetComponentType() const { return s_CompType; }

	void* GetPosition() { return (void*)&m_Position; }
	void* GetRotation() { return (void*)&m_Rotation; }
	void* GetScale() { return (void*)&m_Scale; }

	void* GetmWorld() { return (void*)&m_World; }


	static const unsigned long& GetComponentType() { return s_CompType; }
	static IComponent* CreateComponent( GameObject* owner ) { return new Transformation( owner ); }
};



