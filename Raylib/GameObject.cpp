#include "GameObject.h"
#include "Utils.h"

GameObject::GameObject()
{
	Position = { GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f };
	Rotation = 0;
	Collider = Shape();
	Collider.Type = ShapeType::CIRCLE;
	Collider.CircleData.Radius = 25;
	Texture = Texture2D();
	Tint = WHITE;
}

Vector2 GameObject::GetForwardDirection() const
{
	return Utils::VectorFromAngle(Rotation);
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
	
}

void GameObject::OnCollisionEnter(GameObject* other)
{

}

void GameObject::OnCollisionStay(GameObject* other)
{

}

void GameObject::OnCollisionExit(GameObject* other)
{

}

void GameObject::EarlyDraw()
{

}

void GameObject::Draw()
{
	DrawTexturePro(Texture, { 0, 0, (float)Texture.width, (float)Texture.height },
		{ Position.x, Position.y, (float)Texture.width, (float)Texture.height},
		{ (float)Texture.width * 0.5f, (float)Texture.height * 0.5f }, Rotation * RAD2DEG, Tint);

	switch (Collider.Type)
	{
	case ShapeType::CIRCLE:
		DrawCircleLines((int)Position.x, (int)Position.y, Collider.CircleData.Radius, GREEN);
		break;
	case ShapeType::AABB:
		DrawRectangleLines((int)Position.x, (int)Position.y, Collider.AABBData.HalfExtents.x, Collider.AABBData.HalfExtents.y, GREEN);
		break;
	}
}

void GameObject::LateDraw()
{

}
