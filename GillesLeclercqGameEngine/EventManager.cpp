#include "EventManager.h"

EventManager EventManager::s_Instance = EventManager();

//----------------------------------------------------------------------
// Send Event to subscribed delegates.
void EventManager::SendEvent( IEventPtr evt ) const
{
	auto findIt = m_DelegateMap.find( evt->VGetEvtType() );
	if( findIt != m_DelegateMap.end() )
	{
		for( auto delegates : findIt->second )
		{
			delegates( evt );
		}
	}
	
}

//----------------------------------------------------------------------
// Bind a delegate to a message type.
// Return false if the delegate already existed.
void EventManager::Bind( const unsigned long& evtType, EventDelegate& evtReceiver )
{
	m_DelegateMap[ evtType ].insert( evtReceiver );
}

//----------------------------------------------------------------------
// UnBind a delegate from a message type.
// Return false if the delegate did not exist.
bool EventManager::UnBind( const unsigned long& evtType, EventDelegate& evtReceiver )
{
	auto findIt = m_DelegateMap.find( evtType );
	if( findIt != m_DelegateMap.end() )
	{
		int result = findIt->second.erase( evtReceiver );

		if( result != 0 )
		{
			if( findIt->second.size() == 0 )
			{
				m_DelegateMap.erase( evtType );
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}