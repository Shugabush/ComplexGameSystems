#pragma once

#include "GameObject.h"

class Player : public GameObject
{
	float TargetRotation;

public:
	Vector2 Velocity;
	float MovementSpeed = 5;
	float RotationSpeed = 10;

	virtual void Update() override;
	virtual void LateUpdate() override;
};