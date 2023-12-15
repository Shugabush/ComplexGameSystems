#include "Enemy.h"

void Enemy::Update()
{
	if (TargetObj != nullptr)
	{
		Position = Vector2Lerp(Position, TargetObj->Position, GetFrameTime() * MovementSpeed);
	}
}