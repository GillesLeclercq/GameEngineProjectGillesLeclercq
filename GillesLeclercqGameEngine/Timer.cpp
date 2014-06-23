#include "Timer.h"

Timer::Timer( int TargetFPS )
{
	__int64 TickFreq;
	QueryPerformanceFrequency( (LARGE_INTEGER*)&TickFreq );

	m_SecPerTick = 1.0 / (double)TickFreq;

	m_FrameTimeTarget = 1.0f / (float)TargetFPS;

	m_StartTime = 0;
	m_EndTime = 0;
}

float Timer::GetLastFrameTime()
{
	float frameTime;

	QueryPerformanceCounter( (LARGE_INTEGER*)&m_EndTime );

	frameTime = ( (float)m_EndTime - (float)m_StartTime ) * m_SecPerTick;

	if ( frameTime <= m_FrameTimeTarget )
	{
		float sleepTime = ( m_FrameTimeTarget - frameTime )*1000 ;
		timeBeginPeriod( 1 );
		Sleep( sleepTime );
		timeEndPeriod( 1 );

		return GetLastFrameTime();
	}

	m_StartTime = m_EndTime;

	return frameTime;

}