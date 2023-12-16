#pragma once

#include "Vector2.hpp"
#include "Ray.hpp"

#include "Shape.h"

class GameObject
{
protected:
	std::string Tag;

public:
	static bool RenderCollision;

	class GameManager* Manager;

	GameObject();

	std::string GetTag() const;

	Vector2 Position;
	float Rotation;

	Texture2D Texture;
	Color Tint;

	Vector2 GetForwardDirection() const;

	virtual void Start();

	virtual void EarlyUpdate();
	virtual void Update();
	virtual void LateUpdate();

	virtual void OnCollisionEnter(GameObject* other);
	virtual void OnCollisionStay(GameObject* other);
	virtual void OnCollisionExit(GameObject* other);

	virtual void EarlyDraw();
	virtual void Draw();
	virtual void LateDraw();

	Shape Collider;
};