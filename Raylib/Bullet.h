#pragma once

#include "GameObject.h"

class Bullet : public GameObject
{
	bool HitEnemy;

public:
	Bullet();

	float MovementSpeed = 15;
	Vector2 Velocity;

	virtual void LateUpdate() override;

	virtual void OnCollisionEnter(GameObject* other) override;
};