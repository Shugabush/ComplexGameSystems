#pragma once

#include <Vector2.hpp>

class GameObject
{
public:
	GameObject();

	Vector2 Position;
	float Rotation;

	Texture2D Texture;
	Color Tint;

	virtual void Start();

	virtual void EarlyUpdate(float deltaTime);
	virtual void Update(float deltaTime);
	virtual void LateUpdate(float deltaTime);

	virtual void EarlyDraw();
	virtual void Draw();
	virtual void LateDraw();
};