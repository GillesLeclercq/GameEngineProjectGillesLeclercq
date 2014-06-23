#include "TestInputComponent.h"

#include "GameObject.h"

using namespace std;

//----------------------------------------------------------------------
TestInputComponent::~TestInputComponent()
{
	EventManager::Instance().UnBind( Event_Action::EventType(), fastdelegate::MakeDelegate( this, &TestInputComponent::VProcessAction ) );
	EventManager::Instance().UnBind( Event_AnalogicAction::EventType(), fastdelegate::MakeDelegate( this, &TestInputComponent::VProcessAnalogicAction ) );
	EventManager::Instance().UnBind( Event_StickAction::EventType(), fastdelegate::MakeDelegate( this, &TestInputComponent::VProcessStickAction ) );
}

//----------------------------------------------------------------------
bool TestInputComponent::VInitialize( XmlMediator* pComponent )
{
	EventManager::Instance().Bind( Event_Action::EventType(), fastdelegate::MakeDelegate( this, &TestInputComponent::VProcessAction ) );
	EventManager::Instance().Bind( Event_AnalogicAction::EventType(), fastdelegate::MakeDelegate( this, &TestInputComponent::VProcessAnalogicAction ) );
	EventManager::Instance().Bind( Event_StickAction::EventType(), fastdelegate::MakeDelegate( this, &TestInputComponent::VProcessStickAction ) );
	
	return true;
}

//----------------------------------------------------------------------
void TestInputComponent::VProcessAction( IEventPtr pEvt )
{
	if( auto pActionTranslator = s_pActionTranslator.lock() )
	{
		std::shared_ptr<Event_Action> pEvent = std::static_pointer_cast<Event_Action>( pEvt );
		if( pEvent->GetTarget() == m_pOwner->GetID() )
		{
			switch( (ACTION)pEvent->GetAction() )
			{
				case ACTION_UP:
					cout << "UP" << endl;
					break;
				case ACTION_DOWN:
					cout << "DOWN" << endl;
					break;
				case ACTION_LEFT:
					cout << "LEFT" << endl;
					break;
				case ACTION_RIGHT:
					cout << "RIGHT" << endl;
					break;
			}
		}
		// IGNORE
		return;
	}
}

//----------------------------------------------------------------------
void TestInputComponent::VProcessAnalogicAction( IEventPtr pEvt )
{
	if( auto pActionTranslator = s_pActionTranslator.lock() )
	{
		std::shared_ptr<Event_AnalogicAction> pEvent = std::static_pointer_cast<Event_AnalogicAction>( pEvt );
		if( ( pEvent->GetTarget() == m_pOwner->GetID() ) )
		{
			switch( (ACTION)pEvent->GetAction() )
			{
				case ACTION_LEFTTRIGGER:
					cout << "LT - " << pEvent->GetFactor() << endl;
					break;
				case ACTION_RIGHTTRIGGER:
					cout << "RT - " << pEvent->GetFactor() << endl;
					break;
			}
		}
		// IGNORE
		return;
	}
}

//----------------------------------------------------------------------
void TestInputComponent::VProcessStickAction( IEventPtr pEvt )
{
	if( auto pActionTranslator = s_pActionTranslator.lock() )
	{
		std::shared_ptr<Event_StickAction> pEvent = std::static_pointer_cast<Event_StickAction>( pEvt );
		if( ( pEvent->GetTarget() == m_pOwner->GetID() ) )
		{
			switch( (ACTION)pEvent->GetAction() )
			{
				case ACTION_LEFTSTICK:
					cout << "LS - (" << pEvent->GetPosition().first << ", " << pEvent->GetPosition().second << ")" << endl;
					break;
				case ACTION_RIGHTSTICK:
					cout << "RS - (" << pEvent->GetPosition().first << ", " << pEvent->GetPosition().second << ")" << endl;
					break;
			}
		}
		// IGNORE
		return;
	}
}