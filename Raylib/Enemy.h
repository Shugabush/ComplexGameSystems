#pragma once

#include "GameObject.h"

class Enemy : public GameObject
{
	float TargetRotation;

public:
	virtual void Update() override;
	virtual void LateUpdate() override;

	GameObject* TargetObj;

	float MovementSpeed = 5;
	float RotationSpeed = 1;
};