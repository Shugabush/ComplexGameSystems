#include "Timer.h"

Timer::Timer(float timeLimit)
{
	TimeLimit = timeLimit;
}

float Timer::GetTimeRemaining() const
{
	return TimeLimit - TimeElapsed;
}

float Timer::GetFractionOfTimeElapsed() const
{
	return TimeElapsed / TimeLimit;
}

float Timer::GetFractionOfTimeRemaining() const
{
	return GetTimeRemaining() / TimeLimit;
}

void Timer::Update(float time)
{
	TimeElapsed += time;
	if (TimeElapsed >= TimeLimit)
	{
		TimeElapsed = TimeLimit;
	}
	else if (TimeElapsed < 0)
	{
		TimeElapsed = 0;
	}
}

bool Timer::OutOfTime() const
{
	return TimeElapsed >= TimeLimit;
}

void Timer::Reset()
{
	TimeElapsed = 0;
}