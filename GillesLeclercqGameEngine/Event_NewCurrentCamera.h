#pragma once

#include "IEvent.h"

class Camera;

class Event_NewCurrentCamera : public IEvent
{
private:
	static const unsigned long s_EvtType = 0x69e1a22b;

	int			m_gameObjectID;
	Camera*		m_pCamera;

public:
	Event_NewCurrentCamera( int gameObjectId, Camera* pCamera): m_gameObjectID( gameObjectId ), m_pCamera (pCamera) {}

	int GetGameObjectId() { return m_gameObjectID; }
	Camera* GetCamera() {return m_pCamera ; }

	unsigned long VGetEvtType() const override { return s_EvtType; }
	static unsigned long EventType() { return s_EvtType; }
};
