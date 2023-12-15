#include "Enemy.h"
#include "Utils.h"

void Enemy::Update()
{
	if (TargetObj != nullptr)
	{
		Position = Vector2Lerp(Position, TargetObj->Position, GetFrameTime() * MovementSpeed);

		TargetRotation = Utils::GetLookRotation(Position, TargetObj->Position);
	}
}

void Enemy::LateUpdate()
{
	Rotation = Utils::RotateTowards(Rotation, TargetRotation, GetFrameTime() * RotationSpeed);
}
