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

	virtual void EarlyUpdate();
	virtual void Update();
	virtual void LateUpdate();

	virtual void EarlyDraw();
	virtual void Draw();
	virtual void LateDraw();
};