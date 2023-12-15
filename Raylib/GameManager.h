#pragma once

#include "GameObject.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Shape.h"

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <unordered_map>

class GameManager
{
	// the function signature for any collision detection test
	using CollisionFunc = bool(*)(const Vector2&, const Shape&, const Vector2&, const Shape&);
	using DepenetrationFunc = Vector2(*)(const Vector2&, const Shape&, const Vector2&, const Shape&, float&);

	// a map that take a collision pair and returns the correct function to call
	using CollisionMap = std::unordered_map<ShapeType, CollisionFunc>;
	using DepenetrationMap = std::unordered_map<ShapeType, DepenetrationFunc>;


	std::thread EnemyThread;

	std::vector<GameObject*> AllObjects;

	std::queue<GameObject*> PendingObjects;
	std::vector<GameObject*> MainObjects;
	std::queue<GameObject*> DestroyedObjects;

	CollisionMap collisionCheckers;
	DepenetrationMap collisionDepenetrators;

public:
	EnemyManager* EM;

	GameManager();

	void Init();

	void Update();
	void Draw();

	void SpawnObject(GameObject* obj);
	void DestroyObject(GameObject* obj);

};