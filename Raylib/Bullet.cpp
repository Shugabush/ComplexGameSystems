#include "Bullet.h"
#include "Utils.h"
#include "GameManager.h"

Bullet::Bullet() : GameObject()
{
	Tag = "Bullet";
}

void Bullet::LateUpdate()
{
	GameObject::LateUpdate();

	Position = Vector2Add(Position, Vector2Scale(Velocity, GetFrameTime() * 60 * MovementSpeed));

	if (Utils::PositionIsOutOfBounds(Position))
	{
		Manager->DestroyObject(this);
	}
}

void Bullet::OnCollisionEnter(GameObject* other)
{
	// Make sure the bullet can only destroy one enemy
	// otherwise it will attempt to destroy itself more than once
	// which will cause an error
	if (!HitEnemy && other->GetTag() == "Enemy")
	{
		HitEnemy = true;
		Manager->DestroyObject(other);
		Manager->DestroyObject(this);
	}
}