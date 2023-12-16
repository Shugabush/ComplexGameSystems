#pragma once

#include "GameObject.h"
#include "Timer.h"

class Player : public GameObject
{
	float TargetRotation;

public:

	Vector2 Velocity;
	float MovementSpeed = 5;
	float RotationSpeed = 10;

	Timer BulletCooldown;

	Texture2D BulletTexture;

	virtual void Update() override;
	virtual void LateUpdate() override;
};