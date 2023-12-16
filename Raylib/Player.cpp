#include "Player.h"
#include "GameManager.h"
#include "Utils.h"
#include "Bullet.h"

#include "Ray.hpp"
#include "raymath.h"

#include <iostream>

Player::Player() : GameObject()
{
	Tag = "Player";
}

void Player::Update()
{
	GameObject::Update();
	BulletCooldown.Update(GetFrameTime());

	if (IsKeyDown(KEY_SPACE) && BulletCooldown.OutOfTime())
	{
		BulletCooldown.Reset();

		// Spawn bullet
		Bullet* newBullet = new Bullet();
		newBullet->Texture = BulletTexture;
		newBullet->Position = Position;
		newBullet->Velocity = GetForwardDirection();
		newBullet->Rotation = Rotation;
		Manager->SpawnObject(newBullet);
	}

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
	GameObject::LateUpdate();

	Rotation = Utils::RotateTowards(Rotation, TargetRotation, GetFrameTime() * RotationSpeed);

	Position = Vector2Add(Position, Velocity);
}
