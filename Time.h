#pragma once

class Time;
extern Time *TIME;
class Time
{
public:
	Time();
	~Time();

	void MeasureTheTime();
	float deltaTime() { return m_deltaTime; }
	unsigned long frameRate() { return m_fps; }

private:
	bool m_bPerfHardware = false;
	float m_secPerCount = 0.f;
	float m_deltaTime = 0.f; //Calculate deltaTime
	__int64 m_curTime = 0; //Capture current count
	__int64 m_prevTime = 0; //Initial previous time
	__int64 m_countsPerSec = 0; //Store counts per second

	unsigned long m_fps = 0;
	unsigned long m_frameCnt = 0;
	float m_elapsedTime = 0.f;
};
