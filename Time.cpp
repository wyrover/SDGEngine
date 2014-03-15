#include "Precompiled.h"

namespace sidescroll
{
	Time::Time()
	{
	}

	Time::~Time()
	{
	}

	bool Time::Init()
	{
		if (QueryPerformanceFrequency((LARGE_INTEGER*)&m_countsPerSec))
		{
			m_bPerfHardware = true;
			QueryPerformanceCounter((LARGE_INTEGER*)&m_prevTime);
			m_secPerCount = 1.0f / m_countsPerSec;
		}
		else
		{
			m_bPerfHardware = false;
			m_prevTime = timeGetTime();
			m_secPerCount = 0.001f;
		}

		return true;
	}

	void Time::Start()
	{
		if (m_bPerfHardware)
			QueryPerformanceCounter((LARGE_INTEGER*)&m_curTime);
		else
			m_curTime = timeGetTime();

		m_deltaTime = (m_curTime - m_prevTime) * m_secPerCount;
		m_prevTime = m_curTime;

		m_frameCnt++;
		m_elapsedTime += m_deltaTime;
		if (m_elapsedTime >= 1.0f)
		{
			m_fps = m_frameCnt;

			//Reset elapsed time and frame count
			m_frameCnt = 0;
			m_elapsedTime = 0.0f;
		}
	}
}
