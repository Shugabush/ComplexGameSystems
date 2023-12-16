#pragma once

#include "GameObject.h"

class Bullet : public GameObject
{
public:
	float MovementSpeed = 15;
	Vector2 Velocity;

	virtual void LateUpdate() override;
};