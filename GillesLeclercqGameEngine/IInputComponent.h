#pragma once

#include "IComponent.h"
#include "ActionTranslator.h"

#include "EventManager.h"
#include "Event_Action.h"
#include "Event_AnalogicAction.h"
#include "Event_StickAction.h"

class IInputComponent : public IComponent
{
protected:
	static const unsigned long s_CompType = 0xb063e162;

public:
	IInputComponent( GameObject* pOwner ): IComponent( pOwner ) {}
	virtual ~IInputComponent() {}

	virtual bool VInitialize( XmlMediator* pComponent ) = 0;
	virtual void VProcessAction( IEventPtr pEvt ) = 0;
	virtual void VProcessAnalogicAction( IEventPtr pEvt ) = 0;
	virtual void VProcessStickAction( IEventPtr pEvt ) = 0;

	const unsigned long& VGetComponentType() const override { return s_CompType; }
	static const unsigned long& GetComponentType() { return s_CompType; }

	static WkActionTranslatorPtr s_pActionTranslator;
};