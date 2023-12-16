#pragma once

struct Timer
{
	Timer() = default;
	Timer(float timeLimit);

	float GetTimeRemaining() const;
	float GetFractionOfTimeElapsed() const;
	float GetFractionOfTimeRemaining() const;

	void Update(float time);
	bool OutOfTime() const;
	void Reset();

private:
	float TimeElapsed = 0;
	float TimeLimit = 1;
};