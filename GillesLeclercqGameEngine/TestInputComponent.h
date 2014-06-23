#pragma once

#include "IInputComponent.h"

class TestInputComponent : public IInputComponent
{
public:
	TestInputComponent( GameObject* pOwner ): IInputComponent( pOwner ) {}
	~TestInputComponent();

	bool VInitialize( XmlMediator* pComponent ) override;
	void VProcessAction( IEventPtr pEvt ) override;
	void VProcessAnalogicAction( IEventPtr pEvt ) override;
	void VProcessStickAction( IEventPtr pEvt ) override;

	static IComponent* CreateComponent( GameObject* owner ) { return new TestInputComponent( owner ); }
};