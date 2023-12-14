#pragma once

#include "GameObject.h"

#include <vector>
#include <queue>

class GameManager
{
	std::queue<GameObject*> pendingObjects;
	std::vector<GameObject*> gameObjects;
	std::queue<GameObject*> destroyedObjects;

public:
	void Update(float deltaTime);
	void Draw();

	void SpawnObject(GameObject* obj);
	void DestroyObject(GameObject* obj);

};