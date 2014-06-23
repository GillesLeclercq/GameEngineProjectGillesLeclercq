#pragma once

#include <iostream>

#include "IComponent.h"

class TestComponent : public IComponent 
{
private:
	static const unsigned long s_CompType = 0x17f525ff;

	int m_TestVariable;

public:
	TestComponent( GameObject* pOwner ) : IComponent( pOwner ), m_TestVariable( 0 ) {}
	~TestComponent();

	bool VInitialize( XmlMediator* pComponent ) override;

	void Update( float& frameTime );

	const unsigned long& VGetComponentType() const { return s_CompType; }

	void* GetTestVariable() const { return (void*)&m_TestVariable; }
	void SetTestVariable( void* newValue ) { m_TestVariable = *(int*)newValue; } 
	
	static const unsigned long& GetComponentType() { return s_CompType; }
	static IComponent* CreateComponent( GameObject* owner ) { return new TestComponent( owner ); }
};