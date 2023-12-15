#include "Player.h"
#include "GameManager.h"
#include "Utils.h"

#include "Ray.hpp"
#include "raymath.h"

void Player::Update()
{
	Vector2 targetDir;
	if (IsKeyDown(KEY_UP))
	{
		targetDir.y = -1;
	}
	else if (IsKeyDown(KEY_DOWN))
	{
		targetDir.y = 1;
	}
	else
	{
		targetDir.y = 0;
	}

	if (IsKeyDown(KEY_RIGHT))
	{
		targetDir.x = 1;
	}
	else if (IsKeyDown(KEY_LEFT))
	{
		targetDir.x = -1;
	}
	else
	{
		targetDir.x = 0;
	}

	targetDir = Vector2Normalize(targetDir);

	if (targetDir.x == 0 && targetDir.y == 0)
	{
		TargetRotation = Rotation;

		Velocity = { 0, 0 };
	}
	else
	{
		TargetRotation = Utils::AngleFromVector(targetDir);

		Velocity = Utils::VectorFromAngle(TargetRotation);

		Velocity = Vector2Scale(Vector2Normalize(Velocity), MovementSpeed * GetFrameTime() * 60);
	}
}

void Player::LateUpdate()
{
	Rotation = Utils::RotateTowards(Rotation, TargetRotation, GetFrameTime() * RotationSpeed);

	Position = Vector2Add(Position, Velocity);
}
