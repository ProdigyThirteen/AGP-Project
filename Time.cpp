#include "Time.h"

float Time::m_DeltaTime = 0.0f;
clock_t Time::m_CurrentTime = 0;
clock_t Time::m_PreviousTime = 0;

void Time::Update()
{
	m_PreviousTime = m_CurrentTime;
	m_CurrentTime = clock();

	m_DeltaTime = (m_CurrentTime - m_PreviousTime) / (float)CLOCKS_PER_SEC;
}
