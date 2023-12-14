#include "Player.h"

#include "Ray.hpp"
#include "raymath.h"

void Player::Update(float deltaTime)
{
	if (IsKeyDown(KEY_UP))
	{
		Velocity.y = -1;
	}
	else if (IsKeyDown(KEY_DOWN))
	{
		Velocity.y = 1;
	}
	else
	{
		Velocity.y = 0;
	}

	if (IsKeyDown(KEY_RIGHT))
	{
		Velocity.x = 1;
	}
	else if (IsKeyDown(KEY_LEFT))
	{
		Velocity.x = -1;
	}
	else
	{
		Velocity.x = 0;
	}

	Velocity = Vector2Scale(Vector2Normalize(Velocity), MovementSpeed * deltaTime * 60);

	Position = Vector2Add(Position, Velocity);
}