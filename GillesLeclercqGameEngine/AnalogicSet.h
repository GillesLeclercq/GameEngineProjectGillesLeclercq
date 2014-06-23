#pragma once

#include <memory>

#include "IInputSet.h"
#include "Utilities.h"

class AnalogicSet : virtual public IInputSet
{
private:
	float* m_State;
	float* m_MaxValues;

	int m_ControlNb;

public:
	AnalogicSet( int nbButtons );
	~AnalogicSet();

	float Analogic_GetState( int ID ) const { return ( ID<m_ControlNb ? m_State[ID] : 0.0f ); }

	void Analogic_SetState( int ID, float value ) { if(ID<m_ControlNb) { m_State[ID] = value/m_MaxValues[ID]; } }
	void Analogic_SetMaxValue( int ID, float value ) { if(ID<m_ControlNb && value > 0.0f) { m_MaxValues[ID] = value; } }

	void Analogic_Reset();
};

typedef std::shared_ptr<AnalogicSet> AnalogicSetPtr;
typedef std::weak_ptr<AnalogicSet> WkAnalogicSetPtr;