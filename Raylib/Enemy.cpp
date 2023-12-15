#include "Enemy.h"
#include "Utils.h"

#include <iostream>

void Enemy::Update()
{
	if (TargetObj != nullptr)
	{
		Position = Vector2Lerp(Position, TargetObj->Position, GetFrameTime() * MovementSpeed);
		Rotation = GetLookAtRotation(Position, TargetObj->Position);
	}
}