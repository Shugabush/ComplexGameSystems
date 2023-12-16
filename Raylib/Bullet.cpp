#include "Bullet.h"
#include "Utils.h"
#include "GameManager.h"

void Bullet::LateUpdate()
{
	GameObject::LateUpdate();

	Position = Vector2Add(Position, Vector2Scale(Velocity, GetFrameTime() * 60 * MovementSpeed));

	if (Utils::PositionIsOutOfBounds(Position))
	{
		Manager->DestroyObject(this);
	}
}