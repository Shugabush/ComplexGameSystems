#include "GameManager.h"

#include "EnumUtils.h"

#include <iostream>

void GameManager::CheckCollision(GameObject* a, GameObject* b)
{
	ShapeType pairType = a->Collider.Type | b->Collider.Type;

	// Check every object against every other object
	bool isColliding = collisionCheckers[pairType](a->Position, a->Collider, b->Position, b->Collider);

	if (isColliding)
	{
		if (!GameObjectsEntered[{a, b}])
		{
			a->OnCollisionEnter(b);
			GameObjectsEntered[{a, b}] = true;
			GameObjectsExited[{a, b}] = false;
		}
		a->OnCollisionStay(b);
	}
	else if (!GameObjectsExited[{a, b}] && GameObjectsEntered[{a, b}])
	{
		a->OnCollisionExit(b);
		GameObjectsEntered[{a, b}] = false;
		GameObjectsExited[{a, b}] = true;
	}
}

GameManager::GameManager()
{
	EM = new EnemyManager();
}

void GameManager::Init()
{
	EnemyThread = std::thread(&EnemyManager::Update, EM);

	collisionCheckers[ShapeType::CIRCLE | ShapeType::CIRCLE] = CheckCircleCircle;
	collisionCheckers[ShapeType::CIRCLE | ShapeType::AABB] = CheckCircleAABB;
	collisionCheckers[ShapeType::AABB | ShapeType::AABB] = CheckAABBAABB;

	collisionDepenetrators[ShapeType::CIRCLE | ShapeType::CIRCLE] = DepenetrateCircleCircle;
	collisionDepenetrators[ShapeType::CIRCLE | ShapeType::AABB] = DepenetrateCircleAABB;
	collisionDepenetrators[ShapeType::AABB | ShapeType::AABB] = DepenetrateAABBAABB;
}

void GameManager::Update()
{
	EM->ShouldUpdate = true;

	// Check main objects against each other and enemies
	for (auto i : MainObjects)
	{
		for (auto j : MainObjects)
		{
			if (i == j) { continue; }

			GameObject* left = i;
			GameObject* right = j;

			if (i->Collider.Type > j->Collider.Type)
			{
				left = j;
				right = i;
			}

			CheckCollision(left, right);
		}

		for (auto j : EM->Enemies)
		{
			GameObject* left = i;
			GameObject* right = j;

			if (i->Collider.Type > j->Collider.Type)
			{
				left = j;
				right = i;
			}

			ShapeType pairType = left->Collider.Type | right->Collider.Type;

			CheckCollision(left, right);
		}
	}

	// Check enemies against each other
	for (auto& i : EM->Enemies)
	{
		for (auto j : EM->Enemies)
		{
			if (i == j) { continue; }

			GameObject* left = i;
			GameObject* right = j;

			if (i->Collider.Type > j->Collider.Type)
			{
				left = j;
				right = i;
			}

			CheckCollision(left, right);
		}
	}

	while (!PendingObjects.empty())
	{
		GameObject* obj = PendingObjects.front();
		MainObjects.push_back(obj);
		PendingObjects.pop();
	}

	while (!DestroyedObjects.empty())
	{
		GameObject* obj = DestroyedObjects.front();
		MainObjects.erase(std::remove(MainObjects.begin(), MainObjects.end(), obj), MainObjects.end());
		DestroyedObjects.pop();
		delete obj;
	}

	for (auto obj : MainObjects)
	{
		obj->EarlyUpdate();
	}

	for (auto obj : MainObjects)
	{
		obj->Update();
	}

	for (auto obj : MainObjects)
	{
		obj->LateUpdate();
		obj->Position = Vector2Clamp(obj->Position, { 0, 0 },
			{ (float)GetScreenWidth(), (float)GetScreenHeight() });
	}
}

void GameManager::Draw()
{
	// Wait for enemy manager to update before drawing
	while (EM->ShouldUpdate) {}

	EM->EarlyDraw();
	for (auto obj : MainObjects)
	{
		obj->EarlyDraw();
	}

	EM->Draw();
	for (auto obj : MainObjects)
	{
		obj->Draw();
	}

	EM->LateDraw();
	for (auto obj : MainObjects)
	{
		obj->LateDraw();
	}
}

void GameManager::SpawnObject(GameObject* obj)
{
	obj->Manager = this;
	PendingObjects.push(obj);
}

void GameManager::DestroyObject(GameObject* obj)
{
	auto foundObj = std::find(MainObjects.begin(), MainObjects.end(), obj);
	if (foundObj != MainObjects.end())
	{
 		DestroyedObjects.push(obj);
	}
	else
	{
		auto en = std::find(EM->Enemies.begin(), EM->Enemies.end(), obj);
		if (en != EM->Enemies.end())
		{
			EM->DestroyEnemy(*en._Ptr);
		}
	}
}