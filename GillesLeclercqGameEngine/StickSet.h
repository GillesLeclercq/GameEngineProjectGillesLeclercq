#pragma once

#include <memory>
#include <utility>

#include "IInputSet.h"
#include "Utilities.h"

class StickSet : public IInputSet
{
private:
	std::pair<float, float>* m_StickStates;
	std::pair<float, float>* m_Deadzones;
	float* m_MaxStickValues;

	float m_StickNb;

	float _ComputeFinalState( float& rawState, float& deadzone );

public:
	StickSet( int nbSticks );
	~StickSet();

	std::pair<float, float> Stick_GetState( int ID ) const { return ( ID<m_StickNb ? m_StickStates[ID] : std::pair<float, float>( 0.0f, 0.0f ) ); }

	void Stick_SetState( int ID, float valueX, float valueY );
	void Stick_ProvideDeadzoneSample( int ID, float valueX, float valueY );
	void Stick_SetMaxValue( int ID, float value ) { if(ID<m_StickNb && value > 0.0f) { m_MaxStickValues[ID] = value; } }

	void Stick_ResetState() { for( auto i = 0; i<m_StickNb; i++ ) { m_StickStates[i].first = m_StickStates[i].second = 0.0f; } }
	void Stick_ResetDeadzones() { for( auto i = 0; i<m_StickNb; i++ ) { m_Deadzones[i].first = m_Deadzones[i].second = 0.0f; } }
};

typedef std::shared_ptr<StickSet> StickSetPtr;
typedef std::weak_ptr<StickSet> WkStickSetPtr;