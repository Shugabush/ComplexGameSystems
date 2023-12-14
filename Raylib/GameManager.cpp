#include "GameManager.h"

void GameManager::Update(float deltaTime)
{
	while (!pendingObjects.empty())
	{
		GameObject* obj = pendingObjects.front();
		gameObjects.push_back(obj);
		pendingObjects.pop();
	}

	while (!destroyedObjects.empty())
	{
		GameObject* obj = destroyedObjects.front();
		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), obj), gameObjects.end());
		destroyedObjects.pop();
		delete obj;
	}

	for (auto obj : gameObjects)
	{
		obj->EarlyUpdate(deltaTime);
	}

	for (auto obj : gameObjects)
	{
		obj->Update(deltaTime);
	}

	for (auto obj : gameObjects)
	{
		obj->LateUpdate(deltaTime);
	}
}

void GameManager::Draw()
{
	for (auto obj : gameObjects)
	{
		obj->EarlyDraw();
	}

	for (auto obj : gameObjects)
	{
		obj->Draw();
	}

	for (auto obj : gameObjects)
	{
		obj->LateDraw();
	}
}

void GameManager::SpawnObject(GameObject* obj)
{
	pendingObjects.push(obj);
}

void GameManager::DestroyObject(GameObject* obj)
{
	destroyedObjects.push(obj);
}