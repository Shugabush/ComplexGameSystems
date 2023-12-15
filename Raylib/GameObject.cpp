#include "GameObject.h"

GameObject::GameObject()
{
	Position = { 0, 0 };
	Rotation = 0;
	Texture = Texture2D();
	Tint = WHITE;
}

void GameObject::Start()
{

}

void GameObject::EarlyUpdate()
{
	
}

void GameObject::Update()
{
	
}

void GameObject::LateUpdate()
{
	Position = Vector2Clamp(Position, { 0, 0 }, { (float)GetScreenWidth(), (float)GetScreenHeight() });
}

void GameObject::EarlyDraw()
{

}

void GameObject::Draw()
{
	DrawTexturePro(Texture, { 0, 0, (float)Texture.width, (float)Texture.height },
		{ Position.x, Position.y, (float)Texture.width, (float)Texture.height},
		{ (float)Texture.width * 0.5f, (float)Texture.height * 0.5f }, Rotation, Tint);
}

void GameObject::LateDraw()
{

}
