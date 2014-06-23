#include "StickSet.h"

using namespace std;

//----------------------------------------------------------------------
StickSet::StickSet( int nbSticks )
{
	m_StickStates = new std::pair<float, float>[nbSticks];
	m_Deadzones = new std::pair<float, float>[nbSticks];
	m_MaxStickValues = new float[nbSticks];

	m_StickNb = nbSticks;

	for( auto i = 0; i<nbSticks; i++ )
	{
		m_MaxStickValues[i] = 1.0f;
	}

	Stick_ResetState();
	Stick_ResetDeadzones();
}

//----------------------------------------------------------------------
StickSet::~StickSet()
{
	SAFE_DELETE( m_StickStates );
	SAFE_DELETE( m_Deadzones );
	SAFE_DELETE( m_MaxStickValues );
}

//----------------------------------------------------------------------
// Take the raw state, apply the deadzone calculation and save it as a pourcentage.
void StickSet::Stick_SetState( int ID, float valueX, float valueY )
{
	if( ID<m_StickNb )
	{
		valueX /= m_MaxStickValues[ID];
		valueY /= m_MaxStickValues[ID];

		m_StickStates[ID].first = _ComputeFinalState( valueX, m_Deadzones[ID].first );
		m_StickStates[ID].second = _ComputeFinalState( valueY, m_Deadzones[ID].second );
	}
}

//----------------------------------------------------------------------
// Utility to apply the deadzone calculation.
// Return the final value.
float StickSet::_ComputeFinalState( float& rawState, float& deadzone )
{
	float result = 0.0f;
	float absRawState = abs(rawState); 
	if( absRawState > deadzone )
	{
		result = ( ( absRawState - deadzone ) / ( 1.0f - deadzone ) ); 
		result *= NumericUtilities::Signum( rawState );
	}

	if( result > 1.0f ) result = 1.0f;
	if( result < -1.0f ) result = -1.0f;

	return result;
}

//----------------------------------------------------------------------
void StickSet::Stick_ProvideDeadzoneSample( int ID, float valueX, float valueY )
{
	if( ID < m_StickNb )
	{
		float newXValue, newYValue;
		
		newXValue = abs( max( -1.0f, valueX / m_MaxStickValues[ID] ) );
		newYValue = abs( max( -1.0f, valueY / m_MaxStickValues[ID] ) );

		if( m_Deadzones[ID].first < newXValue )
		{
			m_Deadzones[ID].first = newXValue;
		}

		if( m_Deadzones[ID].second < newYValue )
		{
			m_Deadzones[ID].second = newYValue;
		}
	}
}