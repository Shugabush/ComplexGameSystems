#pragma once

#include <raylib.h>

struct Utils
{
	template<typename T>
	static inline int Sign(const T& value)
	{
		if (value < 0)
		{
			return -1;
		}
		else if (value > 0)
		{
			return 1;
		}
		return 0;
	}

	static inline float GetLookRotation(const Vector2& a, const Vector2& b)
	{
		Vector2 lookDirection = Vector2Normalize(Vector2Subtract(b, a));

		return atan2f(lookDirection.y, lookDirection.x);
	}

	static inline float GetAngle(const Vector2& a, const Vector2& b)
	{
		float dot = Vector2DotProduct(a, b);
		float det = (a.x * a.y) - (b.x * b.y);
		return atan2(det, dot);
	}

	static inline float AngleFromVector(Vector2 vector)
	{
		vector = Vector2Normalize(vector);
		return atan2f(vector.y, vector.x);
	}

	static inline Vector2 VectorFromAngle(const float& angle)
	{
		return { cos(angle), sin(angle) };
	}

	template<typename T>
	static inline T MoveTowards(T current, T target, float maxDelta)
	{
		T deltaMovement = target - current;

		if (-maxDelta < deltaMovement && deltaMovement < maxDelta)
		{
			return target;
		}

		return current + deltaMovement;
	}

	template<typename T>
	static inline T RotateTowards(T current, T target, T maxDelta)
	{
		T deltaAngle = DeltaAngle(current, target);

		if (-maxDelta < deltaAngle && deltaAngle < maxDelta)
		{
			return target;
		}
		target = current + deltaAngle;
		return MoveTowards(current, target, maxDelta);
	}

	template<typename T>
	static inline T DeltaAngle(const T& current, const T& target)
	{
		float delta = target - current;

		if (delta > PI)
		{
			delta -= 2 * PI;
		}

		return delta;
	}
};