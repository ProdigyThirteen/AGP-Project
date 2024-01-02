#pragma once

#include <time.h>

// Static class for handling delta time
class Time
{
private:
	static float m_DeltaTime;
	static clock_t m_CurrentTime;
	static clock_t m_PreviousTime;

public:
	static void Update();
	static float GetDeltaTime() { return m_DeltaTime; }

};

