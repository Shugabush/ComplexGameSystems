#include "GameManager.h"
#include <iostream>

GameManager::GameManager()
{
	EM = new EnemyManager();
}

void GameManager::InitEnemyThread()
{
	EnemyThread = std::thread(&EnemyManager::Update, EM);
}

void GameManager::Update()
{
	EM->ShouldUpdate = true;

	//std::cout << "Updating Game Manager" << std::endl;
	while (!PendingObjects.empty())
	{
		GameObject* obj = PendingObjects.front();
		GameObjects.push_back(obj);
		PendingObjects.pop();
	}

	while (!DestroyedObjects.empty())
	{
		GameObject* obj = DestroyedObjects.front();
		GameObjects.erase(std::remove(GameObjects.begin(), GameObjects.end(), obj), GameObjects.end());
		DestroyedObjects.pop();
		delete obj;
	}

	for (auto obj : GameObjects)
	{
		obj->EarlyUpdate();
	}

	for (auto obj : GameObjects)
	{
		obj->Update();
	}

	for (auto obj : GameObjects)
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

	EM->Draw();

	for (auto obj : GameObjects)
	{
		obj->EarlyDraw();
	}

	for (auto obj : GameObjects)
	{
		obj->Draw();
	}

	for (auto obj : GameObjects)
	{
		obj->LateDraw();
	}
}

void GameManager::SpawnObject(GameObject* obj)
{
	PendingObjects.push(obj);
}

void GameManager::DestroyObject(GameObject* obj)
{
	DestroyedObjects.push(obj);
}