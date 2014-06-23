#pragma once

#include <Windows.h>

class Timer
{
private:
	__int64 m_StartTime;
	__int64 m_EndTime;

	double m_SecPerTick;

	float m_FrameTimeTarget;

public:
	Timer( int TargetFPS );
	~Timer() {}

	void InitializeStartTime() { QueryPerformanceCounter( (LARGE_INTEGER*)&m_StartTime ); }

	float GetLastFrameTime();
};