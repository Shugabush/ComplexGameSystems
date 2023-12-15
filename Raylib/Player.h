#pragma once

#include "GameObject.h"

class Player : public GameObject
{
public:
	Vector2 Velocity;
	float MovementSpeed = 5;

	virtual void Update() override;
};