#include "Utils.h"
#include <raymath.h>
#include <raylib-cpp.hpp>

float GetLookAtRotation(const Vector2& a, const Vector2& b)
{
	Vector2 lookDirection = Vector2Normalize(Vector2Subtract(b, a));

	return atan2f(lookDirection.y, lookDirection.x) * RAD2DEG;
}
