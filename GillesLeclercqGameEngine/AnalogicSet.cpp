#include "AnalogicSet.h"

//----------------------------------------------------------------------
AnalogicSet::AnalogicSet( int nbButtons )
{
	m_State = new float[nbButtons];
	m_MaxValues = new float[nbButtons];
	for( auto i = 0; i<nbButtons; i++ )
	{
		m_State[i] = 0.0f;
		m_MaxValues[i] = 1.0f;
	}

	m_ControlNb = nbButtons;
}

//----------------------------------------------------------------------
AnalogicSet::~AnalogicSet()
{
	SAFE_DELETE( m_State );
	SAFE_DELETE( m_MaxValues );
}

//----------------------------------------------------------------------
void AnalogicSet::Analogic_Reset()
{
	for( auto i = 0; i<m_ControlNb; i++ )
	{
		m_State[i] = 0.0f;
		m_MaxValues[i] = 1.0f;
	}
}