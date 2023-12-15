#pragma once

#include "GameObject.h"
#include "Player.h"
#include "EnemyManager.h"

#include <vector>
#include <queue>
#include <thread>
#include <mutex>

class GameManager
{
	std::thread EnemyThread;

	std::queue<GameObject*> PendingObjects;
	std::vector<GameObject*> GameObjects;
	std::queue<GameObject*> DestroyedObjects;

public:
	EnemyManager* EM;

	GameManager();

	void InitEnemyThread();

	void Update();
	void Draw();

	void SpawnObject(GameObject* obj);
	void DestroyObject(GameObject* obj);

};